#include "Map.h"

Map::Map(int width, int height) {
    this->width = width;
    this->height = height;
    this->map = new Tile**[width];
    for (int xPos = 0; xPos < width; xPos++) {
        this->map[xPos] = new Tile*[height];
        for (int yPos = 0; yPos < height; yPos++) {
            this->map[xPos][yPos] = nullptr;
        }
    }
}

Map::~Map() {}

void Map::setUnit(Unit* unit, int xPos, int yPos) {
    Tile* tile = this->map[xPos][yPos];
    if (tile == nullptr) this->map[xPos][yPos] = new Tile(unit);
    else tile->setUnit(unit);
    unit->setPos(xPos, yPos);
}

Unit* Map::getUnit(int xPos, int yPos) {
    Tile* tile = this->map[xPos][yPos];
    if (tile == nullptr) return nullptr;
    return tile->getUnit();
}

bool Map::isBlank(int xPos, int yPos) {
    if (isBound(xPos, yPos)) return getUnit(xPos, yPos) == nullptr;
    return false;
}