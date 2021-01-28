#include "Game.h"

Game::Game(GameConfig config, Logger* logger) {
    this->config = config;
    this->countdownTicks = config.countdownTicks();
    this->logger = logger;
    logger->log("Creating new game...");
}

Game::~Game() {}

bool Game::isFinished() {
    if (!started) return false;
    for (auto p : players) {
        if (!p.second->isOffline()) return false;
    }
    return true;
}

void Game::addPlayer(Player* p) {
    p->setOwnerId(ownerCounter++);
    p->setScore(0);

    LobbyJoinedMessage* m = new LobbyJoinedMessage(config, p->getOwnerId(), countdownTicks * config.tickTime / 1000);
    p->emit(m);

    PlayerJoinedMessage* pJoinedMessage = new PlayerJoinedMessage(p->getNickname(), p->getOwnerId());
    for (auto kv : players) {
        Player* player = kv.second;
        player->emit(pJoinedMessage); // inform all players about joining p
        PlayerJoinedMessage* playerJoinedMessage = new PlayerJoinedMessage(player->getNickname(), player->getOwnerId());
        p->emit(playerJoinedMessage); // inform p about joining all players
    }
    players.insert(std::pair(p->getOwnerId(), p));
    ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(new IngameMessageFilter());
    if (started) {
        addToGame(p);
        for (auto kv : p->getUnits()) {
            broadcast(new UnitSpawnedMessage(kv.second));
        }
        p->emit(new GameJoinedMessage(factory->getUnits()));
    }
    Client* client = p->getClient();
    GameMessageIdentifier* justCasting = (GameMessageIdentifier*)client->getMessageIdentifier();
    justCasting->onLeaveGame([this, p](SimpleMessage* _){
        _->ignore();
        removePlayer(p);
    });
    justCasting->onChangeGame([this, p](SimpleMessage* _){
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
    GameJoinedMessage* m = new GameJoinedMessage(factory->getUnits());
    for (auto kv : players) {
        kv.second->emit(m);
    }
}

void Game::addToGame(Player* player) {
    spawner->spawnPlayer(player);
    Client* client = player->getClient();
    if (client == nullptr) return; // network disconnected player counts to the game
    GameMessageIdentifier* justCasting = (GameMessageIdentifier*)client->getMessageIdentifier();
    for (auto v: players)
    {
        player->emit(new PlayersScoreChangedMessage (v.second));
    }    
    justCasting->setUnitBatchSize(1000); // idk
    justCasting->onMoveUnits([this, player](MoveUnitsMessage* m){
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
    justCasting->onAttackUnits([this, player](AttackUnitsMessage* m){
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
    for (auto kv : p->getUnits()) {
        removeUnit(kv.second);
    }
    if (players.size() > 0) players.erase(p->getOwnerId());
    bannedPlayers.insert(p);
    if (!p->isOffline()) {
        ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(new NewPlayerMessageFilter());
        p->emit(new GameLeftMessage());
    }
    broadcast(new PlayerLeftMessage(p->getOwnerId()));
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
                    broadcast(new UnitAttackedMessage(unit, targetUnit));
                    if (targetUnit->isDead()) {
                        removeUnit(targetUnit); // death act
                        int ownerid = unit->getOwnerId();
                        Player* scorer = players.at(ownerid);
                        scorer->addScore(10);
                        broadcast(new PlayersScoreChangedMessage(scorer));
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
                if (unit->hasMoved()) broadcast(new UnitMovedMessage(unit));
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
    factory->removeUnit(unit);
    map->unsetUnit(unit);
    deactivatedUnits.insert(unit);
    players.at(unit->getOwnerId())->removeUnit(unit);
    broadcast(new UnitDestroyedMessage(unit));
}
