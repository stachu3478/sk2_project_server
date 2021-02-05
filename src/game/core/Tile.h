#pragma once

#include "Unit.h"

class Tile {
    public:
        Tile() {};
        Tile(UnitPtr unit){ this->unit = unit; };
        virtual ~Tile(){ };

        UnitPtr getUnit(){ return unit; };
        void setUnit(UnitPtr unit) { this->unit = unit; };

    private:
        UnitPtr unit = nullptr;
};