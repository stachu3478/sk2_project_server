#pragma once

#include "cmath"
#include "unordered_set"
#include "unordered_map"
#include "Map.h"
#include "Player.h"
#include "PlayerSpawner.h"
#include "GameConfig.h"
#include "GameMessageIdentifier.h"
#include "IngameMessageFilter.h"
#include "./message/LobbyJoinedMessage.h"
#include "./message/GameJoinedMessage.h"
#include "./message/PlayerJoinedMessage.h"
#include "./message/UnitMovedMessage.h"
#include "./message/UnitAttackedMessage.h"
#include "./message/UnitDestroyedMessage.h"
#include "./message/MoveUnitsMessage.h"

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
        void addToGame(Player* player);
        void kick(Player* player);
        void broadcast(MessageOut* m);
        void removeUnit(Unit* unit);
        std::unordered_map<int, Player*> players;
        bool started = false;
        GameConfig config;
        int ownerCounter = 0;
        int countdownTicks;
        Map* map;
        PlayerSpawner* spawner;
        UnitFactory* factory;
        std::unordered_set<Unit*> activeUnits;
        std::unordered_set<Unit*> deactivatedUnits;
};