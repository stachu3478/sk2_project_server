#pragma once

#include "cmath"
#include "unordered_set"
#include "unordered_map"
#include "Map.h"
#include "Player.h"
#include "PlayerSpawner.h"
#include "GameConfig.h"
#include "GameMessageIdentifier.h"
#include "MessageFilter.h"
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
#include "./message/PlayersScoreChangedMessage.h"

class Game {
    public:
        Game(GameConfig config, Logger* logger);
        virtual ~Game();

        void tick();
        bool isFinished();
        bool isFull() { return players.size() >= config.maxPlayersCountPerGame; };
        bool canJoin(PlayerPtr p) { return !bannedPlayers.contains(p) && (!started || !hasWinner()) && !isFull(); };
        void addPlayer(PlayerPtr p);
        void onChangeGame(std::function<void(PlayerPtr)> cb) { changeGameCallback = cb; };
        void onPlayerRemoved(std::function<void(PlayerPtr)> cb) { removePlayerCallback = cb; };
        void removePlayer(PlayerPtr p);
    private:
        void removePlayerStuff(PlayerPtr p);
        bool isReadyToStart() { return players.size() >= config.minPlayersCountToStart; };
        void start();
        bool hasWinner();
        void addToGame(PlayerPtr player);
        void kick(PlayerPtr player);
        void broadcast(MessageOut* m);
        void removeUnit(UnitPtr unit);
        void removeAllUnits(PlayerPtr p);
        void removeUnitStuff(UnitPtr unit);
        void flush();
        std::unordered_map<int, PlayerPtr> players;
        std::unordered_set<PlayerPtr> bannedPlayers;
        bool started = false;
        GameConfig config;
        int ownerCounter = 0;
        int countdownTicks;
        bool broadcasting = false;
        Map map;
        PlayerSpawner spawner;
        UnitFactory factory;
        std::unordered_set<UnitPtr> activeUnits;
        std::unordered_set<UnitPtr> deactivatedUnits;
        std::function<void(PlayerPtr)> removePlayerCallback;
        std::function<void(PlayerPtr)> changeGameCallback;
        Logger* logger;
};