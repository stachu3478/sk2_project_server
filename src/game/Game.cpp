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
        spawner->spawnPlayer(p);
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
        spawner->spawnPlayer(p);
    }
    started = true;
    GameJoinedMessage* m = new GameJoinedMessage(factory->getUnits());
    for (Player* p : players) {
        p->emit(m);
    }
}

void Game::tick() {
    if (!started) {
        if (isReadyToStart()) start();
        return;
    }
    // TODO: implement
}