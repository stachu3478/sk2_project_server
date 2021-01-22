#pragma once

#include "unordered_map"
#include "Unit.h"

class UnitFactory {
    public:
        UnitFactory() {};
        virtual ~UnitFactory() {};

        Unit* create(char ownerId) { // TODO: fix header code duplication
    Unit* unit = new Unit(idCounter++, ownerId);
    units.insert(std::pair<int, Unit*>(unit->getId(), unit));
    return unit;
};
        std::unordered_map<int, Unit*> getUnits() { return units; };

    private:
        int idCounter = 0;
        std::unordered_map<int, Unit*> units;
};