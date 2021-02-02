#include "GameJoinedMessage.h"

using namespace std;

GameJoinedMessage::~GameJoinedMessage() {}

char* GameJoinedMessage::serialize() {
    char* str = SimpleMessageOut::serialize();
    insertInteger(str + 1, units.size());
    int ptr = 5;
    for (pair<int, UnitPtr> unitPair : units) { // 14 bytes per unit
        UnitPtr unit = unitPair.second;
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