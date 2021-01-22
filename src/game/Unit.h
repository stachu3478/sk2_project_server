#pragma once

class Unit {
    public:
        Unit(int id, int ownerId) { this->id = id; this->ownerId = ownerId; };
        virtual ~Unit() {};

        void setPos(int xPos, int yPos) { this->xPos = xPos; this->yPos = yPos; };
        int getX() { return xPos; };
        int getY() { return yPos; };
        int getId() { return id; };
        int getOwnerId() { return ownerId; };
        char getHitpointsPercent() { return 100; };
    private:
        int id;
        int ownerId;
        int xPos;
        int yPos;
};