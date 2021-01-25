#pragma once

#include "cmath"

struct Point {
    int x;
    int y;
    Point() {};
    Point(int x, int y) { this->x = x; this->y = y; };
    Point(Point* current, int offsetX, int offsetY) { this->x = current->x + offsetX, this->y = current->y + offsetY; };
    double getDistanceTo(Point p) { return hypot(p.x - x, p.y - y); };
    bool isPositive() { return x >= 0 && y >= 0; };
};