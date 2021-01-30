#pragma once

#include <string.h>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class UnitSpawnedMessage: public MessageOut {
    public:
        UnitSpawnedMessage(UnitPtr unit) { this->unit = unit; };
        virtual ~UnitSpawnedMessage();

        char* serialize();
        int length() { return 15; };
    private:
        UnitPtr unit;
};