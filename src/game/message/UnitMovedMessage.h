#pragma once

#include <string.h>
#include <unordered_map>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class UnitMovedMessage : public MessageOut {
    public:
        UnitMovedMessage(UnitPtr unit) { this->toX = unit->getPosition()->x; this->toY = unit->getPosition()->y; this->unitId = unit->getId(); };
        virtual ~UnitMovedMessage();

        char* serialize();
        int length() { return 13; };
    private:
        int toX;
        int toY;
        int unitId;
};