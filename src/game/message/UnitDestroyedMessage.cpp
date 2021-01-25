#include "UnitDestroyedMessage.h"

UnitDestroyedMessage::~UnitDestroyedMessage() {}

char* UnitDestroyedMessage::serialize() {
    char* msg = new char[5];
    msg[0] = 5;
    insertInteger(msg + 1, deadUnitId);
    return msg;
}