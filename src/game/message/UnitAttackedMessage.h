#pragma once

#include <string.h>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class UnitAttackedMessage : public MessageOut {
    public:
        UnitAttackedMessage(UnitPtr attacker, UnitPtr attacked) { this->attackerId = attacker->getId(); this->attackedId = attacked->getId(); this->attackedHitpoints = attacked->getHitpointsPercent(); };
        virtual ~UnitAttackedMessage();

        char* serialize();
        int length() { return 10; };
    private:
        int attackerId;
        int attackedId;
        int attackedHitpoints;
};