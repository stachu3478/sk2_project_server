#pragma once

#include "unordered_set"
#include "Player.h"
#include "GameMessageIdentifier.h"
#include "IngameMessageFilter.h"
#include "./message/LobbyJoinedMessage.h"
#include "./message/GameJoinedMessage.h"
#include "./message/PlayerJoinedMessage.h"

class Game {
    public:
        Game(unsigned int minPlayersToStart, unsigned int maxPlayersCount);
        virtual ~Game();

        void tick() {}; // TODO: implement
        bool isFinished() { return false; };
        bool isFull() { return players.size() >= maxPlayersCount; };
        bool isReadyToStart() { return players.size() >= minPlayersToStart; };
        void addPlayer(Player* p);
        void start(int mapWidth, int mapHeight);
    private:
        std::unordered_set<Player*> players;
        bool started;
        unsigned int minPlayersToStart;
        unsigned int maxPlayersCount;
        int ownerCounter = 0;
};