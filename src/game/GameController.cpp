#include "GameController.h"

GameController::GameController() {
    server = new Server();
    server->setClientCallback([this](Client* c){
        this->addPlayer(new Player(c));
    });
    logger->log("Starting server...");
}

GameController::~GameController() {
    delete logger;
    delete server;
    for (Game* g : games) {
        delete g;
    }
}

void GameController::stop(std::function<void()> callback) {
    logger->log("Closing server...");
    logger->finalize();
    server->shutdown(callback);
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
            logger->log(std::string("Ill player, removing... Nickname: ") + p->getNickname());
            players.erase(p);
            delete p;
        }
    }
    for (Game* g : finishedGames) {
        games.erase(g);
        delete g;
    }
}

void GameController::addPlayer(Player* player) {
    players.insert(player);
    GameMessageIdentifier* messageIdentifier = new GameMessageIdentifier(player);
    messageIdentifier->onPlay([this](PlayMessage* m){
        this->assignPlayer(m);
    });
    messageIdentifier->setMessageFilter(new NewPlayerMessageFilter());
    Client* client = player->getClient();
    client->setMessageIdentifier(messageIdentifier);
}

void GameController::assignPlayer(PlayMessage* m) {
    std::string nick = m->getNickname();
    Player* player = m->getPlayer();
    player->setNickname(nick);
    logger->log(nick + " joined the game");
    assignPlayer(player);
}

void GameController::assignPlayer(Player* p) {
    for (Game* game : games) {
        if (!game->isFull() && game->canJoin(p)) {
            game->addPlayer(p);
            return;
        }
    }
    lastGame = new Game(config, logger);
    games.insert(lastGame);
    lastGame->addPlayer(p);
    lastGame->onChangeGame([this](Player* player) {
        assignPlayer(player);
    });
}