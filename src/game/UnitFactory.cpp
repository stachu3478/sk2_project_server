#include "UnitFactory.h"

UnitPtr UnitFactory::create(char ownerId, int hitpoints, int attackDamage) {
    UnitPtr unit{new Unit(idCounter++, ownerId, hitpoints, attackDamage)};
    units.insert(std::pair<int, UnitPtr>(unit->getId(), unit));
    return unit;
}