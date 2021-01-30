#pragma once

#include <string.h>
#include <unordered_map>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"
#include "../Player.h"

class PlayersScoreChangedMessage : public MessageOut {
    public:
        PlayersScoreChangedMessage(PlayerPtr player) {ownerId = player->getOwnerId(); score = player->getScore();};
        virtual ~PlayersScoreChangedMessage();

        char* serialize();
        int length() { return 6;};
        //1 - typ wiadomosci (10), 1 - ownerdId, 4 - score(int)
    private:
        int ownerId;
        int score;
};