#pragma once

#include <unistd.h>
#include "../events/EpollListener.h"
#include "./ClientDisconnectionCallback.h"

class Client : public EpollListener {
    public:
        Client(int fd);
        virtual ~Client();
        void disconnect();
        void onDisconnection(ClientDisconnectionCallback* cb) { disconnectionCallback = cb; };

        int getFd() { return fd; };
        void trigger() { /* TODO: implement*/ };
        void error() { disconnect(); };
    private:
        int fd;
        ClientDisconnectionCallback* disconnectionCallback;
};