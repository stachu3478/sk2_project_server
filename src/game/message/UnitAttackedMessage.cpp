#include "UnitAttackedMessage.h"

UnitAttackedMessage::~UnitAttackedMessage() {}

char* UnitAttackedMessage::serialize() {
    char* msg = SimpleMessageOut::serialize();
    insertInteger(msg + 1, attackerId);
    insertInteger(msg + 5, attackedId);
    msg[9] = attackedHitpoints;
    return msg;
}