#pragma once

#include <string.h>
#include <unordered_map>
#include "../Unit.h"
#include "SimpleMessageOut.h"
#include "messageHelper.h"

class UnitMovedMessage : public SimpleMessageOut {
    public:
        UnitMovedMessage(UnitPtr unit) { this->toX = unit->getPosition()->x; this->toY = unit->getPosition()->y; this->unitId = unit->getId(); };
        virtual ~UnitMovedMessage();

        char* serialize();
        int length() { return 13; };
        char getType() { return 3; };
    private:
        int toX;
        int toY;
        int unitId;
};