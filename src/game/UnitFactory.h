#pragma once

#include "unordered_map"
#include "Unit.h"

class UnitFactory {
    public:
        UnitFactory() {};
        virtual ~UnitFactory() {};

        Unit* create(char ownerId, int hitpoints, int attackDamage) { // TODO: fix header code duplication
    Unit* unit = new Unit(idCounter++, ownerId, hitpoints, attackDamage);
    units.insert(std::pair<int, Unit*>(unit->getId(), unit));
    return unit;
};
        std::unordered_map<int, Unit*> getUnits() { return units; };
        Unit* getUnit(int id) { return units.at(id); };
        void removeUnit(Unit* unit) { units.erase(unit->getId()); };

    private:
        int idCounter = 0;
        std::unordered_map<int, Unit*> units;
};