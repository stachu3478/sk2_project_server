#pragma once

#include "Point.h"

class Positioned {
    public:
        Positioned() {}
        virtual ~Positioned() {}

        Point* getPosition() { return &position; };
        void setPosition(Point* p) { position.x = p->x; position.y = p->y; };

        double getDistance(Point* p) { return p->getDistanceTo(position); };
        double getDistance(Positioned* p) { return getDistance(p->getPosition()); };
    protected:
        Point position;
};