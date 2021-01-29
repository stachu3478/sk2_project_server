#pragma once

#include "../../net/Message.h"

class GameMessage : public Message {
    public:
        void ignore() { ignored = true; };
    protected:
        bool ignored = false;
};