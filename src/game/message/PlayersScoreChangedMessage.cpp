#include "PlayersScoreChangedMessage.h"

PlayersScoreChangedMessage::~PlayersScoreChangedMessage() {}

char* PlayersScoreChangedMessage::serialize() {
    char* str = new char[6];
    str[0] = 11;
    str[1] = ownerId;
    insertInteger(str + 2, score);
    return str;
}