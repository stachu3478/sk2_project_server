#include "Game.h"

Game::Game(GameConfig config) {
    this->config = config;
    this->countdownTicks = config.countdownTicks();
    printf("Creating new game...\n");
}

Game::~Game() {}

void Game::addPlayer(Player* p) {
    p->setOwnerId(ownerCounter++);

    LobbyJoinedMessage* m = new LobbyJoinedMessage(config, p->getOwnerId(), countdownTicks * config.tickTime / 1000);
    p->emit(m);

    PlayerJoinedMessage* pJoinedMessage = new PlayerJoinedMessage(p->getNickname(), p->getOwnerId());
    for (Player* player : players) {
        player->emit(pJoinedMessage); // inform all players about joining p
        PlayerJoinedMessage* playerJoinedMessage = new PlayerJoinedMessage(player->getNickname(), player->getOwnerId());
        p->emit(playerJoinedMessage); // inform p about joining all players
    }
    players.insert(p);
    ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(new IngameMessageFilter());
    // TODO: add new message subscriptions and filters
    if (started) {
        addToGame(p);
        p->emit(new GameJoinedMessage(factory->getUnits()));
    }
}

void Game::start() {
    if (countdownTicks > 0) {
        countdownTicks--;
        return;
    }
    map = new Map(config.mapWidth, config.mapHeight);
    this->factory = new UnitFactory();
    this->spawner = new PlayerSpawner(map, factory, &config);
    for (Player* p : players) {
        addToGame(p);
    }
    started = true;
    GameJoinedMessage* m = new GameJoinedMessage(factory->getUnits());
    for (Player* p : players) {
        p->emit(m);
    }
}

void Game::addToGame(Player* player) {
    spawner->spawnPlayer(player);
    Client* client = player->getClient();
    if (client == nullptr) return; // network disconnected player counts to the game
    GameMessageIdentifier* justCasting = (GameMessageIdentifier*)client->getMessageIdentifier();
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
            unit->setTargetUnitId(m->getTargetUnitId());
            activeUnits.insert(unit);
        }
    });
}

void Game::kick(Player* player) {
    player->kick("Oszust!");
    players.erase(player);
    // TODO: remove banned player's units
}

void Game::tick() {
    if (!started) {
        if (isReadyToStart()) start();
        return;
    }
    std::unordered_set<Unit*> deactivatedUnits;
    for (Unit* unit : activeUnits) {
        if (unit->isMoving() || unit->isAttacking()) {
            if (unit->isAttacking()) {
                Unit* targetUnit = factory->getUnit(unit->getTargetUnitId());
                if (targetUnit == nullptr) {
                    unit->stopAttacking(); // TODO: choose another target?
                    continue;
                }
                if (unit->getDistance(targetUnit) < config.units.maxAttackDistance) {
                    unit->stopMoving();
                    if (unit->attack(targetUnit, config.units.attackTickColldown)) broadcast(new UnitAttackedMessage(unit, targetUnit));
                } else unit->setTarget(targetUnit->getPosition());
            }
            if (unit->isMoving()) {
                if (map->moveTowards(unit, config.units.moveTickCooldown)) {
                    if (unit->hasMoved()) broadcast(new UnitMovedMessage(unit)); // TODO: unit death
                } else {
                    unit->stopMoving();
                    unit->stopAttacking();
                }
            }
        } else {
            deactivatedUnits.insert(unit);
        }
    }
    for (Unit* unit : deactivatedUnits) activeUnits.erase(unit);
}

void Game::broadcast(MessageOut* m) {
    for (Player* p : players) {
        p->emit(m);
    }
}