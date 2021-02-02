#include "UnitMovedMessage.h"

UnitMovedMessage::~UnitMovedMessage() {}

char* UnitMovedMessage::serialize() {
    char* msg = SimpleMessageOut::serialize();
    insertInteger(msg + 1, unitId);
    insertInteger(msg + 5, toX);
    insertInteger(msg + 9, toY);
    return msg;
}