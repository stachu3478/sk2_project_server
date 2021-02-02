#include "Map.h"

using namespace std;

Map::Map(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    this->map = new Tile[width * height];
}

Map::~Map() {
    delete[] map;
}

void Map::setUnit(UnitPtr unit, Point* pos) {
    Tile* tile = this->map + pos->x + pos->y * width;
    tile->setUnit(unit);
    if (unit != nullptr) unit->setPosition(pos);
}

UnitPtr Map::getUnit(Point* pos) {
    Tile* tile = this->map + pos->x + pos->y * width;
    return tile->getUnit();
}

bool Map::isBlank(Point* pos) {
    if (isBound(pos)) return getUnit(pos) == nullptr;
    return false;
}

bool Map::moveTowards(UnitPtr unit, int cooldown) {
    if (!unit->canMove()) return true;
    Point nextPos = findBetterPositionOutOf(unit->getPosition(), unit->getTarget());
    if (isBound(&nextPos)) {
        setUnit(nullptr, unit->getPosition());
        setUnit(unit, &nextPos);
        unit->setMoveCooldown(cooldown);
        return true;
    }
    return false;
}

Point Map::findBetterPositionOutOf(Point* p0, Point* p2) {
    Point point(-1, -1);
    int bestDistance = p0->getDistanceTo(*p2);
    if (bestDistance == 0) return point;
    if (bestDistance == 1 && !isReachable(p2)) return point;
    Point* best = nullptr;
    bool found = false;
    unordered_set<Point*> searched;
    unordered_map<Point*, Point*> parentPoints;
    unordered_set<int> visited;
    searched.insert(p0);
    int maxDepth = 10;
    int depth = maxDepth++;
    while(!found && searched.size() > 0 && depth-- > 0) {
        unordered_set<Point*> newPoints;
        for (Point* p1 : searched) {
            for (int offsetX = -1; offsetX <= 1; offsetX++) {
                for (int offsetY = -1; offsetY <= 1; offsetY++) {
                    if (offsetY == 0 && offsetX == 0) continue;
                    Point* p = new Point(p1, offsetX, offsetY);
                    if (visited.contains(p->x * width + p->y)) {
                        delete p;
                        continue;
                    }
                    visited.insert(p->x * width + p->y);
                    if (!isReachable(p)) {
                        delete p;
                        continue;
                    }
                    int distance = p1->getDistanceTo(Point(p2, -offsetX, -offsetY));
                    newPoints.insert(p);
                    parentPoints.insert(pair<Point*, Point*>(p, p1));
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
    }
    if (best != nullptr) {
        point.x = best->x;
        point.y = best->y;
    }
    for (auto kv : parentPoints) delete kv.first;
    return point;
}

UnitPtr Map::findUnitInRangeByOwnerId(Point* pos, int ownerId, int range) {
    UnitPtr foundUnit = nullptr;
    rangeIterator(pos, range, [this, ownerId, &foundUnit](UnitPtr unit) {
        if (unit->getOwnerId() == ownerId) {
            foundUnit = unit;
            return false;
        }
        return true;
    });
    return foundUnit;
}

unordered_set<UnitPtr> Map::findUnitsInRangeByOwnerId(PositionedPtr entity, int ownerId, int range) {
    Point* pos = entity->getPosition();
    unordered_set<UnitPtr> foundUnits;
    rangeIterator(pos, range, [this, ownerId, &foundUnits](UnitPtr unit) {
        if (unit->getOwnerId() == ownerId) foundUnits.insert(unit);
        return true;
    });
    return foundUnits;
}

void Map::rangeIterator(Point* p, int range, function<bool(UnitPtr)> callback) {
    Point pos(p->x, p->y);
    int xDir = 1;
    int yDir = 0;
    float toChange = 0.5;
    for (int i = 0; i <= range * 4; i++) {
        for (float j = 0; j < toChange; j++) {
            pos.x += xDir;
            pos.y += yDir;
            if (!isBound(&pos)) continue;
            UnitPtr unit = getUnit(&pos);
            if (unit == nullptr) continue;
            if (!callback(unit)) return;
        }
        const int prevX = xDir;
        xDir = yDir;
        yDir = -prevX;
        toChange += 0.5;
    }
}