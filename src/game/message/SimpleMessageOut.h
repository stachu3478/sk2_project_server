#pragma once

#include <string.h>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class SimpleMessageOut : public MessageOut {
    public:
        virtual char getType() = 0;
        char* serialize() { char* c = new char[length()]; c[0] = getType(); return c; };
        int length() { return 1; };
};

class GameLeftMessage : public SimpleMessageOut {
    public:
        char getType() { return 7; };
};