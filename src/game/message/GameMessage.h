#pragma once

#include "../../net/Message.h"
#include "../Player.h"

class GameMessage : public Message {
    public:
        void setPlayer(Player* p) { player = p; };
        void ignore() { ignored = true; };
    protected:
        Player* player;
        bool ignored = false;
};