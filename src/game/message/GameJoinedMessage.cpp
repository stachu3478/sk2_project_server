#include "GameJoinedMessage.h"

GameJoinedMessage::~GameJoinedMessage() {}

char* GameJoinedMessage::serialize() {
    char* str = new char[13];
    str[0] = 1;
    insertInteger(str + 1, 0); // TODO add unit count
    insertInteger(str + 5, mapWidth);
    insertInteger(str + 9, mapHeight);
    return str;
}