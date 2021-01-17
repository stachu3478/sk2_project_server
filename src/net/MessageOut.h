#pragma once

#include <string>

class MessageOut {
    public:
        virtual char* serialize() = 0;
        virtual int length() = 0;
};