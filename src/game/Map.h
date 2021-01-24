#pragma once

#include <cmath>
#include "Unit.h"
#include "Tile.h"

class Map {
    public:
        Map(int width, int height);
        virtual ~Map();

        Unit* getUnit(int xPos, int yPos);
        void setUnit(Unit* unit, int xPos, int yPos);
        int getWidth() { return width; };
        int getHeight() { return height; };
        bool isBlank(int xPos, int yPos);
        bool isBound(int xPos, int yPos) { return xPos >= 0 && yPos >= 0 && xPos < width && yPos < height; };
        bool moveTowards(Unit* unit, int cooldown);
    private:
        int width;
        int height;
        Tile*** map;
};