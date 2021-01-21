#include "Game.h"

Game::Game(GameConfig config) {
    this->config = config;
    this->countdownTicks = config.countdownTicks();
    printf("Creating new game...\n");
}

Game::~Game() {}

void Game::addPlayer(Player* p) {
    p->setOwnerId(ownerCounter++);

    LobbyJoinedMessage* m = new LobbyJoinedMessage(config, p->getOwnerId(), countdownTicks / config.tickTime);
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
    if (isReadyToStart()) start();
}

void Game::start() {
    started = true;
    GameJoinedMessage* m = new GameJoinedMessage();
    for (Player* p : players) {
        p->emit(m);
    }
}

void Game::tick() {
    if (!started) return;
    if (countdownTicks > 0) {
        countdownTicks--;
        return;
    }
    // TODO: implement
}