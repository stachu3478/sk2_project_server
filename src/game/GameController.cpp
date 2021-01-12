#include "GameController.h"

GameController::GameController() {
    server = new Server();
    server->setClientCallback([this](Client* c){
        printf("Client callback called\n");
        this->addPlayer(new Player(c));
    });
}

GameController::~GameController() {
    delete server;
    for (Game* g : games) {
        delete g;
    }
}

void GameController::start() {
    server->listenAt(portConfig);
    server->setEpollController(new EpollController());
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
    for (Player* p : players) {
        if (p->isIll()) {
            printf("Ill player, removing...\n");
            players.erase(p);
            delete p;
        }
    }
    for (Game* g : finishedGames) {
        games.erase(g);
        delete g;
    }
    //printf("server did some work\n");
}

void GameController::addPlayer(Player* player) {
    players.insert(player);
    GameMessageIdentifier* messageIdentifier = new GameMessageIdentifier(player);
    messageIdentifier->setMessageFilter(new NewPlayerMessageFilter());
    Client* client = player->getClient();
    client->setMessageIdentifier(messageIdentifier);
}