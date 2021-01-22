#include "UnitFactory.h"

UnitFactory::UnitFactory() {}

UnitFactory::~UnitFactory() {}

Unit* UnitFactory::create(char ownerId) {
    Unit* unit = new Unit(idCounter++, ownerId);
    units.insert(std::pair<int, Unit*>(unit->getId(), unit));
    return unit;
}