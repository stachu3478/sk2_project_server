#include "Game.h"

Game::Game(unsigned int minPlayersToStart, unsigned int maxPlayersCount) {
    this->minPlayersToStart = minPlayersToStart;
    this->maxPlayersCount = maxPlayersCount;
    printf("Creating new game...\n");
}

Game::~Game() {}

void Game::addPlayer(Player* p) {
    p->setOwnerId(ownerCounter++);

    LobbyJoinedMessage* m = new LobbyJoinedMessage(minPlayersToStart, p->getOwnerId(), maxPlayersCount);
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

}

void Game::start(int mapWidth, int mapHeight) {
    started = true;
    GameJoinedMessage* m = new GameJoinedMessage(mapWidth, mapHeight);
    for (Player* p : players) {
        p->emit(m);
    }
}