#pragma once

#include <string.h>
#include <unordered_map>
#include "../../core/Unit.h"
#include "../messageHelper.h"
#include "SimpleMessageOut.h"
#include "../../Player.h"

class PlayersScoreChangedMessage : public SimpleMessageOut {
    public:
        PlayersScoreChangedMessage(PlayerPtr player) {ownerId = player->getOwnerId(); score = player->getScore();};
        virtual ~PlayersScoreChangedMessage();

        char* serialize();
        int length() { return 6;};
        char getType() { return 11; };
        //1 - typ wiadomosci (11), 1 - ownerdId, 4 - score(int)
    private:
        int ownerId;
        int score;
};