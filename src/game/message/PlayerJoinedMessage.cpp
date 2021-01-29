#include "PlayerJoinedMessage.h"

PlayerJoinedMessage::~PlayerJoinedMessage() {}

char* PlayerJoinedMessage::serialize() {
    char* msg = new char[length() + 1]; // for \0 at the end of string
    msg[0] = 2;
    msg[1] = ownerId;
    msg[2] = nickname.length();
    strcpy(msg + 3, nickname.c_str());
    return msg;
}