#pragma once

#include "cmath"
#include "Unit.h"
#include "UnitFactory.h"
#include "Player.h"
#include "Map.h"

class PlayerSpawner {
    public:
        PlayerSpawner(Map* map, UnitFactory* factory, int initialUnitCount, int maxClock);
        virtual ~PlayerSpawner();

        void spawnPlayer(Player* player);
        void spawnUnit(Player* player, int xPos, int yPos);
    private:
        Map* map;
        UnitFactory* factory;
        int spawnDirectionClock = 0;
        int initialUnitCount;
        int maxClock;
};