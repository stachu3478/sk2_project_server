#pragma once

#include <sys/epoll.h>

class EpollListener {
    public:
        virtual int getFd() = 0;
        virtual void triggerIn() = 0;
        void triggerOut() {};
        virtual void error() = 0;
};