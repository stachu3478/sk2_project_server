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
    Point* nextPos = findBetterPositionOutOf(unit->getPosition(), unit->getTarget());
    if (nextPos != nullptr) {
        setUnit(nullptr, unit->getPosition());
        setUnit(unit, nextPos);
        unit->setMoveCooldown(cooldown);
        return true;
    }
    return false;
}

Point* Map::findBetterPositionOutOf(Point* p0, Point* p2) {
    int bestDistance = p0->getDistanceTo(*p2);
    if (bestDistance == 0) return nullptr;
    if (bestDistance == 1 && !isReachable(p2)) return nullptr;
    Point* best;
    bool found = false;
    std::unordered_set<Point*> searched;
    std::unordered_map<Point*, Point*> parentPoints;
    std::unordered_set<int> visited;
    searched.insert(p0);
    int maxDepth = 10;
    int depth = maxDepth++;
    while(!found && searched.size() > 0 && depth-- > 0) {
        std::unordered_set<Point*> newPoints;
        for (Point* p1 : searched) {
            for (int offsetX = -1; offsetX <= 1; offsetX++) {
                for (int offsetY = -1; offsetY <= 1; offsetY++) {
                    if (offsetY == 0 && offsetX == 0) continue;
                    Point* p = new Point(p1, offsetX, offsetY);
                    if (visited.contains(p->x * width + p->y)) continue;
                    visited.insert(p->x * width + p->y);
                    if (!isReachable(p)) continue;
                    int distance = p1->getDistanceTo(Point(p2, -offsetX, -offsetY));
                    newPoints.insert(p);
                    parentPoints.insert(std::pair<Point*, Point*>(p, p1));
                    if (distance >= bestDistance) continue;
                    best = p;
                    bestDistance = distance;
                    found = true;
                }
            }
        }
        searched = newPoints;
    }
    if (found) {
        while (parentPoints.at(best) != p0) best = parentPoints.at(best);
        return best;
    }
    return nullptr;
}