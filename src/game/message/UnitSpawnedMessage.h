#pragma once

#include <string.h>
#include "../Unit.h"
#include "SimpleMessageOut.h"
#include "messageHelper.h"

class UnitSpawnedMessage: public SimpleMessageOut {
    public:
        UnitSpawnedMessage(UnitPtr unit) { this->unit = unit; };
        virtual ~UnitSpawnedMessage();

        char* serialize();
        int length() { return 15; };
        char getType() { return 6; };
    private:
        UnitPtr unit;
};