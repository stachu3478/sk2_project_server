#pragma once

#include "unordered_set"
#include "Player.h"
#include "GameMessageIdentifier.h"
#include "IngameMessageFilter.h"
#include "./message/LobbyJoinedMessage.h"
#include "./message/GameJoinedMessage.h"

class Game {
    public:
        Game();
        virtual ~Game();

        void tick() {}; // TODO: implement
        bool isFinished() { return false; };
        int getPlayersCount() { return players.size(); };
        void addPlayer(Player* p, int minimumToStart);
        void start(int mapWidth, int mapHeight);
    private:
        std::unordered_set<Player*> players;
        bool started;
};