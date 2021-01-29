#include "GameController.h"

GameController::GameController() {
    server.setClientCallback([this](Client* c){
        this->addPlayer(new Player(c));
    });
    logger.log("Starting server...");
}

GameController::~GameController() {
    for (Player* player : players) {
        delete player;
    }
    for (Game* g : games) {
        delete g;
    }
}

void GameController::stop(std::function<void()> callback) {
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
    std::unordered_set<Game*> finishedGames;
    for (Game* g : games) {
        g->tick();
        if (g->isFinished()) {
            g->finish();
            finishedGames.insert(g);
        }
    }
    for (Game* g : finishedGames) {
        games.erase(g);
        delete g;
    }
}

void GameController::addPlayer(Player* player) {
    players.insert(player);
    GameMessageIdentifier* messageIdentifier = new GameMessageIdentifier();
    messageIdentifier->onPlay([this, player](PlayMessage* m){
        this->assignPlayer(player, m);
    });
    messageIdentifier->onInvalidMessage([this, player]() {
        logger.log(std::string(player->getNickname()) + " sent invalid message");
        player->kick("Invalid message");
        removePlayer(player);
    });
    messageIdentifier->setMessageFilter(newPlayerMessageFilter);
    Client* client = player->getClient();
    client->setMessageIdentifier(messageIdentifier);
}

void GameController::assignPlayer(Player* p, PlayMessage* m) {
    std::string nick = m->getNickname();
    p->setNickname(nick);
    logger.log(nick + " joined the game");
    assignPlayer(p);
}

void GameController::assignPlayer(Player* p) {
    for (Game* game : games) {
        if (game->canJoin(p)) {
            game->addPlayer(p);
            return;
        }
    }
    Game* lastGame = new Game(config, &logger);
    games.insert(lastGame);
    lastGame->addPlayer(p);
    lastGame->onChangeGame([this](Player* player) {
        assignPlayer(player);
    });
    lastGame->onPlayerRemoved([this](Player* player) {
        if (player->getClient() != nullptr) return;
        removePlayer(player);
    });
}

void GameController::removePlayer(Player* p) {
    for (Game* g : games) {
        g->removePlayer(p);
    }
    players.erase(p);
    logger.log(std::string(p->getNickname()) + " left the game");
}