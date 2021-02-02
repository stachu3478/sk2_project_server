#include "PlayerJoinedMessage.h"

PlayerJoinedMessage::~PlayerJoinedMessage() {}

char* PlayerJoinedMessage::serialize() {
    char* msg = SimpleMessageOut::serialize();
    msg[1] = ownerId;
    msg[2] = nickname.length();
    strcpy(msg + 3, nickname.c_str());
    return msg;
}