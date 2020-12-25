#pragma once

class EpollCloseCallback {
    public:
        virtual void call() = 0;
};