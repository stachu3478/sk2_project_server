#pragma once

#include <unordered_map>
#include "Unit.h"

class UnitFactory {
    public:
        UnitFactory() {};
        virtual ~UnitFactory() {};

        UnitPtr create(char ownerId, int hitpoints, int attackDamage);
        std::unordered_map<int, UnitPtr> getUnits() { return units; };
        UnitPtr getUnit(int id) { return units.contains(id) ? units.at(id) : nullptr; };
        void removeUnit(UnitPtr unit) { units.erase(unit->getId()); };

    private:
        int idCounter = 0;
        std::unordered_map<int, UnitPtr> units;
};