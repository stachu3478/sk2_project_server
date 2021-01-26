#pragma once

#include "cmath"
#include "Point.h"
#include "Unit.h"
#include "UnitFactory.h"
#include "Player.h"
#include "Map.h"
#include "GameConfig.h"

class PlayerSpawner {
    public:
        PlayerSpawner(Map* map, UnitFactory* factory, GameConfig* gameConfig);
        virtual ~PlayerSpawner();

        void spawnPlayer(Player* player);
        void spawnUnit(Player* player, Point* pos);
    private:
        Map* map;
        UnitFactory* factory;
        int spawnDirectionClock = 0;
        int initialUnitCount;
        int maxClock;
        int unitHitpoints;
        int unitAttackDamage;
};