#include "PlayerJoinedMessage.h"

PlayerJoinedMessage::~PlayerJoinedMessage() {}

char* PlayerJoinedMessage::serialize() {
    char* msg = new char[length()];
    msg[0] = 2;
    msg[1] = ownerId;
    msg[2] = nickname.length();
    strcpy(msg + 3, nickname.c_str());
    return msg;
}