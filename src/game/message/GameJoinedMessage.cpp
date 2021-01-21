#include "GameJoinedMessage.h"

GameJoinedMessage::~GameJoinedMessage() {}

char* GameJoinedMessage::serialize() {
    char* str = new char[5];
    str[0] = 1;
    insertInteger(str + 1, 0); // TODO add real units
    return str;
}