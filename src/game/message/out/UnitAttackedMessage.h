#pragma once

#include <string.h>
#include "../../core/Unit.h"
#include "SimpleMessageOut.h"
#include "../messageHelper.h"

class UnitAttackedMessage : public SimpleMessageOut {
    public:
        UnitAttackedMessage(UnitPtr attacker, UnitPtr attacked) { this->attackerId = attacker->getId(); this->attackedId = attacked->getId(); this->attackedHitpoints = attacked->getHitpointsPercent(); };
        virtual ~UnitAttackedMessage();

        char* serialize();
        int length() { return 10; };
        char getType() { return 4; };
    private:
        int attackerId;
        int attackedId;
        int attackedHitpoints;
};