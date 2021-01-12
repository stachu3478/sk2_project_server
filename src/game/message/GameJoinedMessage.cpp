#include "GameJoinedMessage.h"

GameJoinedMessage::~GameJoinedMessage() {}

std::string GameJoinedMessage::serialize() {
    std::string str;
    str.append(1, 1);
    insertInteger(&str, 0); // TODO add unit count
    insertInteger(&str, mapWidth);
    insertInteger(&str, mapHeight);
    return str;
}