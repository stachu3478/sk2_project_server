#pragma once

#include <sstream>

class Message {
    public:
        Message();
        virtual ~Message();

        virtual void readBuffer(std::stringbuf* buffer) = 0;
        virtual bool isComplete() = 0;
};