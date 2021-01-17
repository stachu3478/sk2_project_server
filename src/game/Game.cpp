#include "Game.h"

Game::Game() {
    printf("Creating new game...\n");
}

Game::~Game() {}

void Game::addPlayer(Player* p, int minimumToStart) {
    // TODO: inform players about player joining with PlayerJoinedMessage
    p->setOwnerId(players.size());
    players.insert(p);
    LobbyJoinedMessage* m = new LobbyJoinedMessage(minimumToStart, p->getOwnerId());
    p->emit(m);
    // TODO: add new message subscriptions and filters

}

void Game::start(int mapWidth, int mapHeight) {
    started = true;
    GameJoinedMessage* m = new GameJoinedMessage(mapWidth, mapHeight);
    for (Player* p : players) {
        p->emit(m);
        ((GameMessageIdentifier*)p->getClient()->getMessageIdentifier())->setMessageFilter(new IngameMessageFilter());
    }

}