#include "GameController.h"

GameController::GameController() {
    server = new Server();
    server->setEpollController(new EpollController());
}

GameController::~GameController() {
    delete server;
    for (Game* g : games) {
        delete g;
    }
}

void GameController::start() {
    server->listenAt(portConfig);
    while (server->isAlive()) {
        server->listenFor(50); // TODO: reduce lag by counting delayed time
        tick();
    }
}

void GameController::tick() {
    std::unordered_set<Game*> finishedGames;
    for (Game* g : games) {
        g->tick();
        if (g->isFinished()) {
            finishedGames.insert(g);
        }
    }
    for (Game* g : finishedGames) {
        games.erase(g);
        delete g;
    }
    // printf("server did some work\n");
}

void GameController::addPlayer(Player* p) {
    players.insert(p);
    p->getClient()->setMessageIdentifier(new GameMessageIdentifier(p));
}