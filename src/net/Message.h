#pragma once

#include "Buffer.h"

class Message {
    public:
        virtual void readBuffer(Buffer* buffer) = 0;
        virtual bool isComplete() = 0;
        virtual void receive() = 0;
};