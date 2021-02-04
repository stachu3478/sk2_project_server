#include "Game.h"

using namespace std;

Game::Game(GameConfig* config, Logger* logger) :
map{config->mapWidth, config->mapHeight},
spawner{&map, &factory, config} {
    this->config = config;
    this->countdownTicks = config->countdownTicks();
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

void Game::addPlayer(PlayerPtr p) {
    p->setOwnerId(ownerCounter++);
    p->setScore(0);

    LobbyJoinedMessage m(config, p->getOwnerId(), countdownTicks * config->tickTime / 1000);
    p->emit(&m);

    PlayerJoinedMessage pJoinedMessage(p->getNickname(), p->getOwnerId());
    for (auto kv : players) {
        PlayerPtr player = kv.second;
        player->emit(&pJoinedMessage); // inform all players about joining p
        PlayerJoinedMessage playerJoinedMessage(player->getNickname(), player->getOwnerId());
        p->emit(&playerJoinedMessage); // inform p about joining all players
    }
    players.insert(pair(p->getOwnerId(), p));
    GameMessageIdentifier* gameMessageIdentifier = p->getMessageIdentifier();
    gameMessageIdentifier->setMessageFilter(ingameMessageFilter);
    if (started) {
        addToGame(p);
        for (auto kv : p->getUnits()) {
            UnitSpawnedMessage m(kv.second);
            broadcast(&m);
        }
        GameJoinedMessage m(factory.getUnits());
        p->emit(&m);
    }
    gameMessageIdentifier->onLeaveGame([this, p](SimpleMessage* _){
        _->ignore();
        removePlayer(p);
        flush();
        p->flush();
    });
    gameMessageIdentifier->onChangeGame([this, p](SimpleMessage* _){
        _->ignore();
        removePlayer(p);
        changeGameCallback(p);
        flush();
        p->flush();
    });
    flush();
}

void Game::start() {
    if (countdownTicks > 0) {
        countdownTicks--;
        return;
    }
    for (auto kv : players) {
        addToGame(kv.second);
    }
    started = true;
    GameJoinedMessage m(factory.getUnits());
    broadcast(&m);
}

void Game::addToGame(PlayerPtr player) {
    spawner.spawnPlayer(player);
    ClientPtr client = player->getClient();
    if (client == nullptr) return; // network disconnected player counts to the game
    GameMessageIdentifier* gameMessageIdentifier = player->getMessageIdentifier();
    for (auto v: players) {
        PlayersScoreChangedMessage m(v.second);
        player->emit(&m);
    }
    gameMessageIdentifier->onMoveUnits([this, player](MoveUnitsMessage* m){
        int* unitIds = m->getUnitIds();
        for (int i = 0; i < m->getUnitCount(); i++) {
            UnitPtr unit = factory.getUnit(unitIds[i]);
            if (unit == nullptr) continue;
            if (unit->getOwnerId() != player->getOwnerId()) {
                kick(player); // Wants to use not his units
                return;
            }
            unit->stopAttacking();
            Point target(m->getTargetX(), m->getTargetY());
            unit->setTarget(&target);
            activeUnits.insert(unit);
        }
    });
    gameMessageIdentifier->onAttackUnits([this, player](AttackUnitsMessage* m){
        int* unitIds = m->getUnitIds();
        UnitPtr targetUnit = factory.getUnit(m->getTargetUnitId());
        if (targetUnit == nullptr) return;
        if (targetUnit->getOwnerId() == player->getOwnerId()) {
            kick(player); // Wants to attack himself
            return;
        }
        for (int i = 0; i < m->getUnitCount(); i++) {
            UnitPtr unit = factory.getUnit(unitIds[i]);
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

void Game::kick(PlayerPtr player) {
    removePlayer(player);
    player->kick("Oszust!");
    //metoda do skreślenia gracza
}

void Game::removePlayer(PlayerPtr p) {
    if (!players.contains(p->getOwnerId())) return;
    if (players.size() > 0) players.erase(p->getOwnerId());
    removePlayerStuff(p);
}

void Game::removePlayerStuff(PlayerPtr p) {
    GameLeftMessage gameLeftMessage;
    PlayerLeftMessage playerLeftMessage(p->getOwnerId());
    removeAllUnits(p);
    bannedPlayers.insert(p);
    if (!p->isOffline()) {
        p->getMessageIdentifier()->setMessageFilter(newPlayerMessageFilter);
        p->emit(&gameLeftMessage);
    }
    broadcast(&playerLeftMessage);
    removePlayerCallback(p);
    //metoda do skreślenia gracza
}

void Game::tick() {
    if (!started) {
        if (isReadyToStart()) start();
        else countdownTicks = config->countdownTicks();
        return;
    }
    unordered_set<UnitPtr> toBeActivated;
    for (UnitPtr unit : activeUnits) {
        if (unit->isIdle()) {
            deactivatedUnits.insert(unit);
            continue;
        }
        if (unit->isAttacking()) {
            UnitPtr targetUnit = factory.getUnit(unit->getTargetUnitId());
            if (targetUnit == nullptr) {
                UnitPtr anotherTarget = map.findUnitInRangeByOwnerId(unit->getPosition(), unit->getTargetUnitOwnerId(), config->units.maxAttackDistance);
                if (anotherTarget != nullptr) {
                    unit->setTargetUnit(anotherTarget); // choose another target near him
                    continue;
                }
                anotherTarget = map.findUnitInRangeByOwnerId(unit->getTarget(), unit->getTargetUnitOwnerId(), config->units.maxAttackDistance);
                if (anotherTarget != nullptr) unit->setTargetUnit(anotherTarget); // choose another target near last target
                else unit->stopAttacking(); 
                continue;
            }
            if (unit->getDistance(dynamic_pointer_cast<Positioned>(targetUnit)) < config->units.maxAttackDistance) {
                unit->stopMoving();
                if (unit->attack(targetUnit, config->units.attackTickColldown)) {
                    UnitAttackedMessage m(unit, targetUnit);
                    broadcast(&m);
                    if (targetUnit->isDead()) {
                        removeUnit(targetUnit); // death act
                        int ownerid = unit->getOwnerId();
                        PlayerPtr scorer = players.at(ownerid);
                        scorer->addScore(10);
                        PlayersScoreChangedMessage mScore(scorer);
                        broadcast(&mScore);
                        //metoda dodaje punkty getOwnerId(unit)
                    } else if (targetUnit->isIdle()) {
                        for (UnitPtr avenger : map.findUnitsInRangeByOwnerId(dynamic_pointer_cast<Positioned>(targetUnit), targetUnit->getOwnerId(), config->units.maxAttackDistance)) {
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
            if (map.moveTowards(unit, config->units.moveTickCooldown)) {
                if (unit->hasMoved()) {
                    UnitMovedMessage m(unit);
                    broadcast(&m);
                }
            } else {
                unit->stopMoving();
                unit->stopAttacking();
            }
        }
    }
    for (UnitPtr unit : toBeActivated) {
        activeUnits.insert(unit);
    }
    for (UnitPtr unit : deactivatedUnits) {
        activeUnits.erase(unit);
    }
    deactivatedUnits.clear();
    if (broadcasting) flush();
}

void Game::broadcast(MessageOut* m) {
    for (auto kv : players) {
        PlayerPtr p = kv.second;
        p->emit(m);
    }
    broadcasting = true;
}

void Game::removeUnit(UnitPtr unit) {
    removeUnitStuff(unit);
    players.at(unit->getOwnerId())->removeUnit(unit);
}

void Game::removeAllUnits(PlayerPtr p) {
    for (auto kv : p->getUnits()) {
        removeUnitStuff(kv.second);
    }
    p->clearUnits();
}

void Game::removeUnitStuff(UnitPtr unit) {
    UnitDestroyedMessage m(unit);
    unit->die();
    factory.removeUnit(unit);
    map.unsetUnit(unit);
    deactivatedUnits.insert(unit);
    broadcast(&m);
}

void Game::flush() {
    for (auto kv : players) {
        kv.second->flush();
    }
    broadcasting = false;
}
