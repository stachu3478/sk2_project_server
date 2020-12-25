#pragma once

#include <sys/epoll.h>
#include <array>
#include <unistd.h>
#include "EpollListener.h"
#include "EpollCloseCallback.h"

class PollingError : std::exception {};

class EpollController {
    public:
        EpollController();
        void addListener(EpollListener* l);
        void removeListener(EpollListener* l);
        void listen(int miliseconds = -1);
        void close();
        void onClose(EpollCloseCallback* e) { closeCallback = e; };
    private:
        int fd;
        bool shouldClose;
        EpollCloseCallback* closeCallback;
        std::array<struct epoll_event, 32> events;
};
