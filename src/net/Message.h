#pragma once

#include <sstream>

class Message {
    public:
        virtual void readBuffer(std::stringbuf* buffer) = 0;
        virtual bool isComplete() = 0;
        virtual void receive() = 0;
};