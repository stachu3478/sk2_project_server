#pragma once

#include "Unit.h"

class Tile {
    public:
        Tile(Unit* unit){ this->unit = unit; };
        virtual ~Tile(){ };

        Unit* getUnit(){ return unit; };
        void setUnit(Unit* unit) { this->unit = unit; };

    private:
        Unit* unit = nullptr;
};