#pragma once

#include <cmath>
#include <algorithm>

class Unit {
    public:
        Unit(int id, int ownerId) { this->id = id; this->ownerId = ownerId; };
        virtual ~Unit() {};

        void setPos(int xPos, int yPos) { this->xPos = xPos; this->yPos = yPos; };
        void setPos(int xPos, int yPos, int cooldown) { this->xPos = xPos; this->yPos = yPos; this->moveCooldown = cooldown; this->moved = true; };
        void setMoveCooldown(int c) { this->moveCooldown = c; this->moved = true; };
        int getX() { return xPos; };
        int getY() { return yPos; };
        int getTargetX() { return targetX; };
        int getTargetY() { return targetY; };
        void setTarget(int xPos, int yPos) { this->targetX = xPos; this->targetY = yPos; };
        int getId() { return id; };
        int getOwnerId() { return ownerId; };
        char getHitpointsPercent() { return 100; };
        bool canMove() { return moveCooldown-- <= 0; moved = false; };
        bool canAttack() { return attackCooldown-- <= 0; };
        int getDistanceTo(int x, int y) { return std::max(abs(xPos - x), abs(yPos - y)); };
        bool hasMoved() { bool m = moved; moved = false; return m; };
    private:
        int id;
        int ownerId;
        int xPos;
        int yPos;
        int targetX;
        int targetY;
        int moveCooldown = 0;
        int attackCooldown = 0;
        bool moved = false;
};