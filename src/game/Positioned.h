#pragma once

#include "Point.h"
#include <memory>

class Positioned {
    public:
        Positioned() {}
        virtual ~Positioned() {}

        Point* getPosition() { return &position; };
        void setPosition(Point* p) { position.x = p->x; position.y = p->y; };

        double getDistance(Point* p) { return p->getDistanceTo(position); };
        double getDistance(std::shared_ptr<Positioned> p) { return getDistance(p->getPosition()); };
    protected:
        Point position;
};

typedef std::shared_ptr<Positioned> PositionedPtr;