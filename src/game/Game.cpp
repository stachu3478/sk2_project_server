#include "Game.h"

Game::Game(GameConfig config, Logger* logger) {
    this->config = config;
    this->countdownTicks = config.countdownTicks();
    this->logger = logger;
    logger->log("Creating new game...");
}

Game::~Game() {
    delete factory;
    delete spawner;
}

bool Game::isFinished() {
    if (!started) return false;
    for (auto p : players) {
        if (!p.second->isOffline()) return false;
    }
    return true;
}

bool Game::hasWinner() {
    bool livingPlayer = false;
    for (auto p : players) {
        if (p.second->getUnitCount() > 0) {
            if (livingPlayer) return false;
            livingPlayer = true;
        }
    }
    return livingPlayer;
}

void Game::addPlayer(Player* p) {
    p->setOwnerId(ownerCounter++);
    p->setScore(0);

    LobbyJoinedMessage m(config, p->getOwnerId(), countdownTicks * config.tickTime / 1000);
    p->emit(&m);

    PlayerJoinedMessage pJoinedMessage(p->getNickname(), p->getOwnerId());
    for (auto kv : players) {
        Player* player = kv.second;
        player->emit(&pJoinedMessage); // inform all players about joining p
        PlayerJoinedMessage playerJoinedMessage(player->getNickname(), player->getOwnerId());
        p->emit(&playerJoinedMessage); // inform p about joining all players
    }
    players.insert(std::pair(p->getOwnerId(), p));
    ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(ingameMessageFilter);
    if (started) {
        addToGame(p);
        for (auto kv : p->getUnits()) {
            UnitSpawnedMessage m(kv.second);
            broadcast(&m);
        }
        GameJoinedMessage m(factory->getUnits());
        p->emit(&m);
    }
    Client* client = p->getClient();
    GameMessageIdentifier* gameMessageIdentifier = (GameMessageIdentifier*)client->getMessageIdentifier();
    gameMessageIdentifier->onLeaveGame([this, p](SimpleMessage* _){
        _->ignore();
        removePlayer(p);
    });
    gameMessageIdentifier->onChangeGame([this, p](SimpleMessage* _){
        _->ignore();
        removePlayer(p);
        changeGameCallback(p);
    });
}

void Game::start() {
    if (countdownTicks > 0) {
        countdownTicks--;
        return;
    }
    map = new Map(config.mapWidth, config.mapHeight);
    this->factory = new UnitFactory();
    this->spawner = new PlayerSpawner(map, factory, &config);
    for (auto kv : players) {
        addToGame(kv.second);
    }
    started = true;
    GameJoinedMessage m(factory->getUnits());
    for (auto kv : players) {
        kv.second->emit(&m);
    }
}

void Game::addToGame(Player* player) {
    spawner->spawnPlayer(player);
    Client* client = player->getClient();
    if (client == nullptr) return; // network disconnected player counts to the game
    GameMessageIdentifier* gameMessageIdentifier = (GameMessageIdentifier*)client->getMessageIdentifier();
    for (auto v: players)
    {
        PlayersScoreChangedMessage m(v.second);
        player->emit(&m);
    }
    gameMessageIdentifier->onMoveUnits([this, player](MoveUnitsMessage* m){
        int* unitIds = m->getUnitIds();
        for (int i = 0; i < m->getUnitCount(); i++) {
            Unit* unit = factory->getUnit(unitIds[i]);
            if (unit == nullptr) continue;
            if (unit->getOwnerId() != player->getOwnerId()) {
                kick(player); // Wants to use not his units
                return;
            }
            unit->stopAttacking();
            unit->setTarget(new Point(m->getTargetX(), m->getTargetY()));
            activeUnits.insert(unit);
        }
    });
    gameMessageIdentifier->onAttackUnits([this, player](AttackUnitsMessage* m){
        int* unitIds = m->getUnitIds();
        Unit* targetUnit = factory->getUnit(m->getTargetUnitId());
        if (targetUnit == nullptr) return;
        if (targetUnit->getOwnerId() == player->getOwnerId()) {
            kick(player); // Wants to attack himself
            return;
        }
        for (int i = 0; i < m->getUnitCount(); i++) {
            Unit* unit = factory->getUnit(unitIds[i]);
            if (unit == nullptr) continue;
            if (unit->getOwnerId() != player->getOwnerId()) {
                kick(player); // Wants to use not his units
                return;
            }
            unit->setTargetUnit(targetUnit);
            activeUnits.insert(unit);
        }
    });
}

void Game::kick(Player* player) {
    removePlayer(player);
    player->kick("Oszust!");
    //metoda do skreślenia gracza
}

void Game::removePlayer(Player* p) {
    if (!players.contains(p->getOwnerId())) return;
    if (players.size() > 0) players.erase(p->getOwnerId());
    removePlayerStuff(p);
}

void Game::removePlayerStuff(Player* p) {
    GameLeftMessage gameLeftMessage;
    PlayerLeftMessage playerLeftMessage(p->getOwnerId());
    removeAllUnits(p);
    bannedPlayers.insert(p);
    if (!p->isOffline()) {
        ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(newPlayerMessageFilter);
        p->emit(&gameLeftMessage);
    }
    broadcast(&playerLeftMessage);
    removePlayerCallback(p);
    //metoda do skreślenia gracza
}

void Game::tick() {
    if (!started) {
        if (isReadyToStart()) start();
        else countdownTicks = config.countdownTicks();
        return;
    }
    std::unordered_set<Unit*> toBeActivated;
    for (Unit* unit : activeUnits) {
        if (unit->isIdle()) {
            deactivatedUnits.insert(unit);
            continue;
        }
        if (unit->isAttacking()) {
            Unit* targetUnit = factory->getUnit(unit->getTargetUnitId());
            if (targetUnit == nullptr) {
                Unit* anotherTarget = map->findUnitInRangeByOwnerId(unit->getPosition(), unit->getTargetUnitOwnerId(), config.units.maxAttackDistance);
                if (anotherTarget != nullptr) {
                    unit->setTargetUnit(anotherTarget); // choose another target near him
                    continue;
                }
                anotherTarget = map->findUnitInRangeByOwnerId(unit->getTarget(), unit->getTargetUnitOwnerId(), config.units.maxAttackDistance);
                if (anotherTarget != nullptr) unit->setTargetUnit(anotherTarget); // choose another target near last target
                else unit->stopAttacking(); 
                continue;
            }
            if (unit->getDistance(targetUnit) < config.units.maxAttackDistance) {
                unit->stopMoving();
                if (unit->attack(targetUnit, config.units.attackTickColldown)) {
                    UnitAttackedMessage m(unit, targetUnit);
                    broadcast(&m);
                    if (targetUnit->isDead()) {
                        removeUnit(targetUnit); // death act
                        int ownerid = unit->getOwnerId();
                        Player* scorer = players.at(ownerid);
                        scorer->addScore(10);
                        PlayersScoreChangedMessage mScore(scorer);
                        broadcast(&mScore);
                        //metoda dodaje punkty getOwnerId(unit)
                    } else if (targetUnit->isIdle()) {
                        for (Unit* avenger : map->findUnitsInRangeByOwnerId(targetUnit, targetUnit->getOwnerId(), config.units.maxAttackDistance)) {
                            if (avenger->isIdle()) {
                                avenger->setTargetUnit(unit); // revenge
                                toBeActivated.insert(avenger);
                            }
                        }
                    }
                }
            } else unit->setTarget(targetUnit->getPosition());
        }
        if (unit->isMoving()) {
            if (map->moveTowards(unit, config.units.moveTickCooldown)) {
                UnitMovedMessage m(unit);
                if (unit->hasMoved()) broadcast(&m);
            } else {
                unit->stopMoving();
                unit->stopAttacking();
            }
        }
    }
    for (Unit* unit : toBeActivated) {
        activeUnits.insert(unit);
    }
    for (Unit* unit : deactivatedUnits) {
        activeUnits.erase(unit);
        if (unit->isDead()) delete unit;
    }
    deactivatedUnits.clear();
}

void Game::broadcast(MessageOut* m) {
    for (auto kv : players) {
        Player* p = kv.second;
        p->emit(m);
    }
}

void Game::removeUnit(Unit* unit) {
    removeUnitStuff(unit);
    players.at(unit->getOwnerId())->removeUnit(unit);
}

void Game::removeAllUnits(Player* p) {
    for (auto kv : p->getUnits()) {
        removeUnitStuff(kv.second);
    }
    p->clearUnits();
}

void Game::removeUnitStuff(Unit* unit) {
    factory->removeUnit(unit);
    map->unsetUnit(unit);
    deactivatedUnits.insert(unit);
    broadcast(new UnitDestroyedMessage(unit));
}
