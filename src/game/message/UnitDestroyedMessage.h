#pragma once

#include <string.h>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class UnitDestroyedMessage : public MessageOut {
    public:
        UnitDestroyedMessage(Unit* dead) { this->deadUnitId = dead->getId(); };
        virtual ~UnitDestroyedMessage();

        char* serialize();
        int length() { return 5; };
    private:
        int deadUnitId;
};