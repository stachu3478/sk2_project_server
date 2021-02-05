#pragma once

#include "cmath"
#include "core/Point.h"
#include "core/Unit.h"
#include "core/Map.h"
#include "core/UnitFactory.h"
#include "Player.h"
#include "core/GameConfig.h"

class PlayerSpawner {
    public:
        PlayerSpawner(Map* map, UnitFactory* factory, GameConfig* gameConfig);
        virtual ~PlayerSpawner();

        void spawnPlayer(PlayerPtr player);
        void spawnUnit(PlayerPtr player, Point pos);
    private:
        Map* map;
        UnitFactory* factory;
        int spawnDirectionClock = 0;
        int initialUnitCount;
        int maxClock;
        int unitHitpoints;
        int unitAttackDamage;
};