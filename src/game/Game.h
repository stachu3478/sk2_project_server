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
#include "NewPlayerMessageFilter.h"
#include "Logger.h"
#include "./message/SimpleMessage.h"
#include "./message/SimpleMessageOut.h"
#include "./message/LobbyJoinedMessage.h"
#include "./message/GameJoinedMessage.h"
#include "./message/PlayerJoinedMessage.h"
#include "./message/PlayerLeftMessage.h"
#include "./message/UnitMovedMessage.h"
#include "./message/UnitAttackedMessage.h"
#include "./message/UnitDestroyedMessage.h"
#include "./message/UnitSpawnedMessage.h"
#include "./message/MoveUnitsMessage.h"

class Game {
    public:
        Game(GameConfig config, Logger* logger);
        virtual ~Game();

        void tick();
        bool isFinished();
        bool isFull() { return players.size() >= config.maxPlayersCountPerGame; };
        bool canJoin(Player* p) { return !bannedPlayers.contains(p); };
        void addPlayer(Player* p);
        void onChangeGame(std::function<void(Player*)> cb) { changeGameCallback = cb; };
    private:
        bool isReadyToStart() { return players.size() >= config.minPlayersCountToStart; };
        void start();
        void addToGame(Player* player);
        void removePlayer(Player* p);
        void kick(Player* player);
        void broadcast(MessageOut* m);
        void removeUnit(Unit* unit);
        std::unordered_map<int, Player*> players;
        std::unordered_set<Player*> bannedPlayers;
        bool started = false;
        GameConfig config;
        int ownerCounter = 0;
        int countdownTicks;
        Map* map;
        PlayerSpawner* spawner;
        UnitFactory* factory;
        std::unordered_set<Unit*> activeUnits;
        std::unordered_set<Unit*> deactivatedUnits;
        std::function<void(Player*)> changeGameCallback;
        Logger* logger;
};