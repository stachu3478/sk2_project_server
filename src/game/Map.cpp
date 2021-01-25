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

void Map::setUnit(Unit* unit, Point* pos) {
    Tile* tile = this->map[pos->x][pos->y];
    if (tile == nullptr) this->map[pos->x][pos->y] = new Tile(unit);
    else tile->setUnit(unit);
    if (unit != nullptr) unit->setPosition(pos);
}

Unit* Map::getUnit(Point* pos) {
    Tile* tile = this->map[pos->x][pos->y];
    if (tile == nullptr) return nullptr;
    return tile->getUnit();
}

bool Map::isBlank(Point* pos) {
    if (isBound(pos)) return getUnit(pos) == nullptr;
    return false;
}

bool Map::moveTowards(Unit* unit, int cooldown) {
    if (!unit->canMove()) return true;
    Point* target = unit->getTarget();
    int bestDistance = unit->getDistance(target);
    int bestOffsetX;
    int bestOffsetY;
    bool found = false;
    for (int offsetX = -1; offsetX <= 1; offsetX++) {
        for (int offsetY = -1; offsetY <= 1; offsetY++) {
            if (!isReachable(new Point(unit->getPosition(), offsetX, offsetY))) continue;
            int distance = unit->getDistance(new Point(target, -offsetX, -offsetY));
            if (distance >= bestDistance) continue;
            bestOffsetX = offsetX;
            bestOffsetY = offsetY;
            bestDistance = distance;
            found = true;
        }
    }
    if (found) {
        setUnit(nullptr, unit->getPosition());
        setUnit(unit, new Point(unit->getPosition(), bestOffsetX, bestOffsetY));
        unit->setMoveCooldown(cooldown);
        return true;
    }
    return false;
}