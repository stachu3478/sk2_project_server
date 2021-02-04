#pragma once

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <cstring>
#include <exception>
#include "Buffer.h"
#include "Message.h"

class MessageReadError : public std::exception {};

class MessageIdentifier {
    public:
        MessageIdentifier() {};
        virtual ~MessageIdentifier() {};

        void setFd(int fd) { this->fd = fd; };
        int readMessages();
    protected:
        virtual Message* createMessage(Buffer* buffer) = 0;
    private:
        void createMessages();
        Message* lastMessage = nullptr;
        int fd;
        char buff[1024];
        Buffer buffer;
        int bufferLength;
        bool bufferInitialized = false;
};