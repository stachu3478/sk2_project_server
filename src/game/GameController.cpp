#include "GameController.h"

using namespace std;

GameController::GameController() {
    server.setClientCallback([this](Client* c){
        PlayerPtr p{new Player(c)};
        this->addPlayer(p);
    });
    logger.log("Starting server...");
}

GameController::~GameController() {
    for (Game* g : games) {
        delete g;
    }
}

void GameController::stop(function<void()> callback) {
    logger.log("Closing server...");
    logger.finalize();
    server.shutdown(callback);
}

void GameController::start() {
    server.listenAt(config.port);
    while (server.isAlive()) {
        server.listenFor(config.tickTime); // TODO: reduce lag by counting delayed time
        tick();
    }
}

void GameController::tick() {
    unordered_set<Game*> finishedGames;
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
}

void GameController::addPlayer(PlayerPtr player) {
    players.insert(player);
    GameMessageIdentifier* messageIdentifier = player->getMessageIdentifier();
    messageIdentifier->onPlay([this, player](PlayMessage* m){
        this->assignPlayer(player, m);
    });
    messageIdentifier->onInvalidMessage([this, player]() {
        logger.log(string(player->getNickname()) + " sent invalid message");
        player->kick("Invalid message");
        removePlayer(player);
    });
    messageIdentifier->setMessageFilter(newPlayerMessageFilter);
    Client* client = player->getClient();
    client->setMessageIdentifier(messageIdentifier);
}

void GameController::assignPlayer(PlayerPtr p, PlayMessage* m) {
    string nick = m->getNickname();
    p->setNickname(nick);
    logger.log(nick + " joined the game");
    assignPlayer(p);
}

void GameController::assignPlayer(PlayerPtr p) {
    for (Game* game : games) {
        if (game->canJoin(p)) {
            game->addPlayer(p);
            return;
        }
    }
    Game* lastGame = new Game(&config, &logger);
    games.insert(lastGame);
    lastGame->addPlayer(p);
    lastGame->onChangeGame([this](PlayerPtr player) {
        assignPlayer(player);
    });
    lastGame->onPlayerRemoved([this](PlayerPtr player) {
        if (player->getClient() != nullptr) return;
        removePlayer(player);
    });
}

void GameController::removePlayer(PlayerPtr p) {
    for (Game* g : games) {
        g->removePlayer(p);
    }
    players.erase(p);
    logger.log(string(p->getNickname()) + " left the game");
    // delete p; // FIXME: seg fault
}