#include "UnitFactory.h"

UnitFactory::UnitFactory() {}

UnitFactory::~UnitFactory() {}

Unit* UnitFactory::create(char ownerId, int hitpoints, int attackDamage) {
    Unit* unit = new Unit(idCounter++, ownerId, hitpoints, attackDamage);
    units.insert(std::pair<int, Unit*>(unit->getId(), unit));
    return unit;
}