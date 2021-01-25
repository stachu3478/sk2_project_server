#include "Unit.h"

bool Unit::attack(Unit* unit, int cooldown) {
    if (attackCooldown-- <= 0) {
        unit->hitpoints -= attackDamage;
        this->attackCooldown = cooldown;
        return true;
    }
    return false;
}