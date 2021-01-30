#pragma once

#include <cmath>
#include <unordered_set>
#include <functional>
#include "Point.h"
#include "Positioned.h"
#include "Unit.h"
#include "Tile.h"

class Map {
    public:
        Map(unsigned int width, unsigned int height);
        virtual ~Map();

        UnitPtr getUnit(Point* pos);
        void setUnit(UnitPtr unit, Point* pos);
        void unsetUnit(UnitPtr unit) { setUnit(nullptr, unit->getPosition()); };
        int getWidth() { return width; };
        int getHeight() { return height; };
        bool isBlank(Point* p);
        bool isBound(Point* p) { return p->isPositive() && (unsigned int)p->x < width && (unsigned int)p->y < height; };
        bool isReachable(Point* p) { return isBlank(p); };
        bool moveTowards(UnitPtr unit, int cooldown);
        UnitPtr findUnitInRangeByOwnerId(Point* pos, int ownerId, int range);
        std::unordered_set<UnitPtr> findUnitsInRangeByOwnerId(PositionedPtr entity, int ownerId, int range);
    private:
        Point findBetterPositionOutOf(Point* p1, Point* p2);
        void rangeIterator(Point* p, int range, std::function<bool(UnitPtr)> callback);
        unsigned int width;
        unsigned int height;
        Tile* map;
};