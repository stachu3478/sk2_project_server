#pragma once

#include <sys/epoll.h>
#include <array>
#include <unistd.h>
#include <chrono>
#include <functional>
#include <signal.h>
#include "EpollListener.h"

class PollingError : std::exception {};

class EpollController {
    public:
        EpollController();
        void addListener(EpollListener* l);
        void removeListener(EpollListener* l);
        void listen(int miliseconds = -1);
        void close(std::function<void(void)> callback);
    private:
        int fd;
        bool shouldClose;
        std::function<void(void)> closeCallback;
        std::array<struct epoll_event, 32> events;
};
