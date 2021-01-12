#pragma once

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <unordered_set>
#include <functional>
#include "../events/EpollListener.h"
#include "../events/EpollController.h"
#include "./Client.h"

class ConnectException : public std::exception {};

class Server : public EpollListener {
    public:
        Server();
        virtual ~Server();
        
        bool isAlive() { return alive; };
        void listenAt(int port);
        void listenFor(int miliseconds) { epollController->listen(miliseconds); };
        void shutdown(std::function<void(void)> callback);
        void setClientCallback(std::function<void(Client*)> c) { clientCallback = c; };
        void setEpollController(EpollController* e) { epollController = e; e->addListener(this); };
        void clientDisconnected(Client* c);

        int getFd() { return sockFd; };
        void triggerIn();
        void error();
    private:
        bool alive = false;
        sockaddr_in addr;
        int sockFd;
        std::function<void(Client*)> clientCallback;
        std::unordered_set<Client*> clients;
        EpollController* epollController;
        std::function<void()> closeCallback;
        void closeAll();
};

