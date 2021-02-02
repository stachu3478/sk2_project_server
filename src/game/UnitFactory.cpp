#include "UnitFactory.h"

using namespace std;

UnitPtr UnitFactory::create(char ownerId, int hitpoints, int attackDamage) {
    UnitPtr unit{new Unit(idCounter++, ownerId, hitpoints, attackDamage)};
    units.insert(pair<int, UnitPtr>(unit->getId(), unit));
    return unit;
}