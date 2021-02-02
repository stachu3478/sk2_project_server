#include "UnitDestroyedMessage.h"

UnitDestroyedMessage::~UnitDestroyedMessage() {}

char* UnitDestroyedMessage::serialize() {
    char* msg = SimpleMessageOut::serialize();
    insertInteger(msg + 1, deadUnitId);
    return msg;
}