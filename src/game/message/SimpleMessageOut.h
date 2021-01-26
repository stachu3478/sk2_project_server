#pragma once

#include <string.h>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class SimpleMessageOut : public MessageOut {
    public:
        SimpleMessageOut();
        virtual ~SimpleMessageOut();

        virtual char getType();
        char* serialize() { char* c = new char[1]; c[0] = getType(); return c; };
        int length() { return 1; };
};

class GameLeftMessage : public SimpleMessageOut {
    public:
        char getType() { return 7; };
};