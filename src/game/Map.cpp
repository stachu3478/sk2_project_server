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
    if (unit != nullptr) unit->setPos(xPos, yPos);
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

bool Map::moveTowards(Unit* unit, int cooldown) {
    if (!unit->canMove()) return true;
    int xPos = unit->getTargetX();
    int yPos = unit->getTargetY();
    int bestDistance = hypot(unit->getX() - xPos, abs(unit->getY() - yPos));
    int bestOffsetX;
    int bestOffsetY;
    bool found = false;
    for (int offsetX = -1; offsetX <= 1; offsetX++) {
        for (int offsetY = -1; offsetY <= 1; offsetY++) {
            if (!isBound(unit->getX() + offsetX, unit->getY() + offsetY)
            || !isBlank(unit->getX() + offsetX, unit->getY() + offsetY) ) continue;
            int distance = hypot(unit->getX() - xPos + offsetX, unit->getY() - yPos + offsetY);
            if (distance >= bestDistance) continue;
            bestOffsetX = offsetX;
            bestOffsetY = offsetY;
            bestDistance = distance;
            found = true;
        }
    }
    if (found) {
        setUnit(nullptr, unit->getX(), unit->getY());
        setUnit(unit, unit->getX() + bestOffsetX, unit->getY() + bestOffsetY);
        unit->setMoveCooldown(cooldown);
        return true;
    }
    return false;
}