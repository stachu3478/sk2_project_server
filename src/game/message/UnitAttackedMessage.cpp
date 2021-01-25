#include "UnitAttackedMessage.h"

UnitAttackedMessage::~UnitAttackedMessage() {}

char* UnitAttackedMessage::serialize() {
    char* msg = new char[10];
    msg[0] = 4;
    insertInteger(msg + 1, attackerId);
    insertInteger(msg + 5, attackedId);
    msg[9] = attackedHitpoints;
    return msg;
}