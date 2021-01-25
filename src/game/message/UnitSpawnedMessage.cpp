#include "UnitSpawnedMessage.h"

UnitSpawnedMessage::~UnitSpawnedMessage() {}

char* UnitSpawnedMessage::serialize() {
    char* str = new char[15];
    str[0] = 6;
    insertInteger(str + 1, unit->getId());
    str[5] = unit->getHitpointsPercent();
    str[6] = unit->getOwnerId();
    insertInteger(str + 7, unit->getPosition()->x);
    insertInteger(str + 11, unit->getPosition()->y);
    return str;
}