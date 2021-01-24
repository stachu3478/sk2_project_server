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
    this->spawner = new PlayerSpawner(map, factory, config.initialUnitCount, config.maxPlayersCountPerGame);
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
                kick(player);
                return;
            }
            unit->setTarget(m->getTargetX(), m->getTargetY());
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
        if (map->moveTowards(unit, config.unitMoveTickColldown)) {
            if (unit->hasMoved()) broadcast(new UnitMovedMessage(unit));
        } else deactivatedUnits.insert(unit);
    }
    for (Unit* unit : deactivatedUnits) activeUnits.erase(unit);
}

void Game::broadcast(MessageOut* m) {
    for (Player* p : players) {
        p->emit(m);
    }
}