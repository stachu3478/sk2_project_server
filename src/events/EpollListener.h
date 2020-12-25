#pragma once

#include <sys/epoll.h>

class EpollListener {
    public:
        virtual int getFd() = 0;
        virtual void trigger() = 0;
        virtual void error() = 0;
};