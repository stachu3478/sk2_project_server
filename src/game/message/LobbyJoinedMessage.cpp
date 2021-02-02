#include "LobbyJoinedMessage.h"

LobbyJoinedMessage::~LobbyJoinedMessage() {}

char* LobbyJoinedMessage::serialize() {
    char* msg = SimpleMessageOut::serialize();
    msg[1] = config->minPlayersCountToStart;
    msg[2] = ownerId;
    msg[3] = config->maxPlayersCountPerGame;
    msg[4] = countdownSeconds;
    insertInteger(msg + 5, config->mapWidth);
    insertInteger(msg + 9, config->mapHeight);
    return msg;
}