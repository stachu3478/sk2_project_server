#include "GameJoinedMessage.h"

GameJoinedMessage::~GameJoinedMessage() {}

char* GameJoinedMessage::serialize() {
    char* str = new char[5 + units.size() * 14];
    str[0] = 1;
    insertInteger(str + 1, units.size());
    int ptr = 5;
    for (std::pair<int, Unit*> unitPair : units) { // 14 bytes per unit
        Unit* unit = unitPair.second;
        insertInteger(str + ptr, unit->getId());
        ptr += 4;
        str[ptr++] = unit->getHitpointsPercent();
        str[ptr++] = unit->getOwnerId();
        insertInteger(str + ptr, unit->getPosition()->x);
        ptr += 4;
        insertInteger(str + ptr, unit->getPosition()->y);
        ptr += 4;
    }
    return str;
}