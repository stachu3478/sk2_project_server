#pragma once

#include <string.h>
#include "../../core/Unit.h"
#include "SimpleMessageOut.h"
#include "../messageHelper.h"

class UnitDestroyedMessage : public SimpleMessageOut {
    public:
        UnitDestroyedMessage(UnitPtr dead) { this->deadUnitId = dead->getId(); };
        virtual ~UnitDestroyedMessage();

        char* serialize();
        int length() { return 5; };
        char getType() { return 5; };
    private:
        int deadUnitId;
};