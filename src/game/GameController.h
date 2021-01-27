#pragma once

#include <unordered_set>
#include <functional>
#include <stdio.h>
#include <stdlib.h>
#include "../net/Server.h"
#include "../net/ClientCallback.h"
#include "../events/EpollController.h"
#include "GameConfig.h"
#include "NewPlayerMessageFilter.h"
#include "GameMessageIdentifier.h"
#include "Game.h"
#include "Player.h"
#include "Logger.h"

class GameController {
    public:
        GameController();
        virtual ~GameController();

        void start();
        void stop(std::function<void()> callback);
        void setServerPort(int port) { portConfig = port; };
    private:
        void tick();
        void addPlayer(Player* p);
        void assignPlayer(PlayMessage* m);
        void assignPlayer(Player* p);
        std::unordered_set<Game*> games;
        Game* lastGame;
        std::unordered_set<Player*> players;
        int portConfig = 34780;
        GameConfig config;
        Server* server;
        Logger* logger = new Logger("log.txt");
};