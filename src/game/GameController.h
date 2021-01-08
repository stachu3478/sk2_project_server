#pragma once

#include <unordered_set>
#include "../net/Server.h"
#include "../net/ClientCallback.h"
#include "../net/ServerCloseCallback.h"
#include "../events/EpollController.h"
#include "GameMessageIdentifier.h"
#include "Game.h"
#include "Player.h"

class GameController {
    public:
        GameController();
        virtual ~GameController();

        void start();
        void stop() { server->shutdown(); } ;
        void onStopped(ServerCloseCallback* c) { server->onShutdown(c); };
        void setServerPort(int port) { portConfig = port; };
    private:
        void tick();
        void addPlayer(Player* p);
        std::unordered_set<Game*> games;
        std::unordered_set<Player*> players;
        int portConfig = 34780;

        Server* server;

        class GameClientCallback : public ClientCallback {
            public:
                GameClientCallback(GameController* c) { controller = c; };
                void call(Client* c) { controller->addPlayer(new Player(c)); };
            private:
                GameController* controller;
        };
};