#pragma once

#include "cmath"
#include "unordered_set"
#include "Map.h"
#include "Player.h"
#include "PlayerSpawner.h"
#include "GameConfig.h"
#include "GameMessageIdentifier.h"
#include "IngameMessageFilter.h"
#include "./message/LobbyJoinedMessage.h"
#include "./message/GameJoinedMessage.h"
#include "./message/PlayerJoinedMessage.h"

class Game {
    public:
        Game(GameConfig config);
        virtual ~Game();

        void tick();
        bool isFinished() { return false; };
        bool isFull() { return players.size() >= config.maxPlayersCountPerGame; };
        void addPlayer(Player* p);
    private:
        bool isReadyToStart() { return players.size() >= config.minPlayersCountToStart; };
        void start();
        std::unordered_set<Player*> players;
        bool started;
        GameConfig config;
        int ownerCounter = 0;
        int countdownTicks;
        Map* map;
        PlayerSpawner* spawner;
        UnitFactory* factory;
};