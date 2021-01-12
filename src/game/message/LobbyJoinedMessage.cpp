#include "LobbyJoinedMessage.h"

LobbyJoinedMessage::~LobbyJoinedMessage() {}

std::string LobbyJoinedMessage::serialize() {
    char msg[3];
    msg[0] = 0;
    msg[1] = minPlayersToStart;
    msg[2] = ownerId;
    std::string str(msg);
    return str;
}