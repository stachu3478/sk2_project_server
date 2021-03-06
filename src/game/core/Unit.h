#pragma once

#include <cmath>
#include <algorithm>
#include <memory>
#include "Point.h"
#include "Positioned.h"

class Unit : public Positioned {
    public:
        Unit(int id, int ownerId, int hitpoints, int attackDamage) { this->id = id; this->ownerId = ownerId; this->maxHitpoints = this->hitpoints = hitpoints; this->attackDamage = attackDamage; };
        virtual ~Unit() {};

        void setPos(Point* p, int cooldown) { setPosition(p); this->moveCooldown = cooldown; this->moved = true; };
        void setMoveCooldown(int c) { this->moveCooldown = c; this->moved = true; };
        Point* getTarget() { return &target; };
        void setTarget(Point* target) { this->target.x = target->x; this->target.y = target->y; moving = true; };
        void setTargetUnit(std::shared_ptr<Unit> unit) { this->targetUnitId = unit->getId(); targetOwnerId = unit->getOwnerId(); setTarget(unit->getPosition()); attacking = true; };
        int getTargetUnitId() { return targetUnitId; };
        int getTargetUnitOwnerId() { return targetOwnerId; };
        int getId() { return id; };
        int getOwnerId() { return ownerId; };
        char getHitpointsPercent() { return (char) ((100 * hitpoints) / maxHitpoints); };
        bool canMove() { return moveCooldown-- <= 0; moved = false; };
        bool canAttack() { return attackCooldown-- <= 0; };
        bool hasMoved() { bool m = moved; moved = false; return m; };
        bool isMoving() { return moving; };
        bool isAttacking() { return attacking; };
        void die() { hitpoints = 0; };
        bool isDead() { return hitpoints <= 0; };
        bool isIdle() { return isDead() || (!isMoving() && !isAttacking()); };
        void stopMoving() { this->moving = false; };
        void stopAttacking() { this->attacking = false; };
        bool attack(std::shared_ptr<Unit> unit, int cooldown);
    private:
        int id;
        int ownerId;
        int maxHitpoints;
        int hitpoints;
        int attackDamage;
        Point target{-1, -1};
        int targetUnitId;
        int targetOwnerId;
        int moveCooldown = 0;
        int attackCooldown = 0;
        bool moved = false;
        bool moving = false;
        bool attacking = false;
};

typedef std::shared_ptr<Unit> UnitPtr;