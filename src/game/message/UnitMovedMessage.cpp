#include "UnitMovedMessage.h"

UnitMovedMessage::~UnitMovedMessage() {}

char* UnitMovedMessage::serialize() {
    char* msg = new char[13];
    msg[0] = 3;
    insertInteger(msg + 1, unitId);
    insertInteger(msg + 5, toX);
    insertInteger(msg + 9, toY);
    return msg;
}