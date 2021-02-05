#pragma once

#include <unordered_set>
#include <unordered_map>
#include "cmath"
#include "core/Map.h"
#include "Player.h"
#include "PlayerSpawner.h"
#include "core/GameConfig.h"
#include "GameMessageIdentifier.h"
#include "core/MessageFilter.h"
#include "core/Logger.h"
#include "./message/in/SimpleMessage.h"
#include "./message/out/SimpleMessageOut.h"
#include "./message/out/LobbyJoinedMessage.h"
#include "./message/out/GameJoinedMessage.h"
#include "./message/out/PlayerJoinedMessage.h"
#include "./message/out/PlayerLeftMessage.h"
#include "./message/out/UnitMovedMessage.h"
#include "./message/out/UnitAttackedMessage.h"
#include "./message/out/UnitDestroyedMessage.h"
#include "./message/out/UnitSpawnedMessage.h"
#include "./message/in/MoveUnitsMessage.h"
#include "./message/out/PlayersScoreChangedMessage.h"

class Game {
    public:
        Game(GameConfig* config, Logger* logger);
        virtual ~Game();

        void tick();
        bool isFinished();
        bool isFull() { return players.size() >= config->maxPlayersCountPerGame; };
        bool canJoin(PlayerPtr p) { return !bannedPlayers.contains(p) && (!started || !hasWinner()) && !isFull(); };
        void addPlayer(PlayerPtr p);
        void onChangeGame(std::function<void(PlayerPtr)> cb) { changeGameCallback = cb; };
        void onPlayerRemoved(std::function<void(PlayerPtr)> cb) { removePlayerCallback = cb; };
        void removePlayer(PlayerPtr p);
    private:
        void removePlayerStuff(PlayerPtr p);
        bool isReadyToStart() { return players.size() >= config->minPlayersCountToStart; };
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
        GameConfig* config;
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