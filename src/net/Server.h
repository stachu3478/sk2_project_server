#pragma once

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <unordered_set>
#include "ClientCallback.h"
#include "../events/EpollListener.h"
#include "../events/EpollController.h"
#include "../events/EpollCloseCallback.h"
#include "./ServerCloseCallback.h"
#include "./Client.h"

class ConnectException : public std::exception {};

class Server : public EpollListener {
    public:
        Server();
        void listenAt(int port);
        void shutdown();
        void setClientCallback(ClientCallback* c) { clientCallback = c; };
        void setEpollController(EpollController* e) { epollController = e; };
        void onShutdown(ServerCloseCallback* c) { closeCallback = c; };
        int getFd() { return sockFd; };
        void trigger();
        void error();
    private:
        sockaddr_in addr;
        int sockFd;
        ClientCallback* clientCallback;
        std::unordered_set<Client*> clients;
        EpollController* epollController;
        ServerCloseCallback* closeCallback;
        void closeAll();
        class ServerEpollCloseCallback : public EpollCloseCallback {
            public:
                ServerEpollCloseCallback(Server* s) { server = s; };
                void call() { server->closeAll(); }
            private:
                Server* server;
        };
};

