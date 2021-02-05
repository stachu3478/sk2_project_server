#pragma once

#include "../../../net/Message.h"

enum GMessage {
    PLAY = 0,
    MOVE_UNITS = 2,
    ATTACK_UNITS = 3,
    LEAVE_GAME = 4,
    CHANGE_GAME = 5
};

class GameMessage : public Message {
    public:
        void ignore() { ignored = true; };
    protected:
        bool ignored = false;
};