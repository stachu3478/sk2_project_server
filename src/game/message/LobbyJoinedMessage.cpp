#include "LobbyJoinedMessage.h"

LobbyJoinedMessage::~LobbyJoinedMessage() {}

char* LobbyJoinedMessage::serialize() {
    char* msg = new char[4];
    msg[0] = 0;
    msg[1] = minPlayersToStart;
    msg[2] = ownerId;
    msg[3] = maxPlayersCount;
    return msg;
}