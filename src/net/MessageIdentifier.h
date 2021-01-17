#pragma once

#include <unistd.h>
#include <sstream>
#include <exception>
#include "Message.h"

class MessageReadError : public std::exception {};

class MessageIdentifier {
    public:
        MessageIdentifier();
        virtual ~MessageIdentifier();

        void setFd(int fd) { this->fd = fd; };
        void readMessages();
    protected:
        virtual Message* createMessage(std::stringbuf* buffer) = 0;
    private:
        void createMessages();
        Message* lastMessage;
        int fd;
        char buff[1024];
        std::stringbuf* buffer;
        bool bufferInitialized = false;
};