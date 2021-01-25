#pragma once

#include <cmath>
#include "Point.h"
#include "Unit.h"
#include "Tile.h"

class Map {
    public:
        Map(int width, int height);
        virtual ~Map();

        Unit* getUnit(Point* pos);
        void setUnit(Unit* unit, Point* pos);
        void unsetUnit(Unit* unit) { setUnit(nullptr, unit->getPosition()); };
        int getWidth() { return width; };
        int getHeight() { return height; };
        bool isBlank(Point* p);
        bool isBound(Point* p) { return p->isPositive() && p->x < width && p->y < height; };
        bool isReachable(Point* p) { return isBlank(p); };
        bool moveTowards(Unit* unit, int cooldown);
    private:
        int width;
        int height;
        Tile*** map;
};