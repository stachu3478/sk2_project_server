#include "PlayersScoreChangedMessage.h"

PlayersScoreChangedMessage::~PlayersScoreChangedMessage() {}

char* PlayersScoreChangedMessage::serialize() {
    char* str = SimpleMessageOut::serialize();
    str[1] = ownerId;
    insertInteger(str + 2, score);
    return str;
}