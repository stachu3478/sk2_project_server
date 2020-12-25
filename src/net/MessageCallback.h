#pragma once

#include "Message.h"

class MessageCallback {
    public:
        virtual void call(Message* m) = 0;
};