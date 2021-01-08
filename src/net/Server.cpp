#include "Server.h"

Server::Server() {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

Server::~Server() {}

void Server::listenAt(int port) {
    addr.sin_port = htons((uint16_t)port);
    sockFd = socket(PF_INET, SOCK_STREAM, 0);
    if (sockFd == -1) {
        perror("socket failed");
        throw new ConnectException();
    }
    int fail = bind(sockFd, (sockaddr*) &addr, sizeof(addr));
    if (fail) {
        perror("bind failed");
        throw new ConnectException();
    }
    fail = listen(sockFd, 1);
    if (fail) {
        perror("listen failed");
        throw new ConnectException();
    }
    alive = true;
    printf("Listening on *:%d\n", port);
}

void Server::shutdown() {
    epollController->onClose(new ServerEpollCloseCallback(this));
    epollController->close();
    alive = false;
}

void Server::closeAll() {
    for (Client* c : clients) {
        c->disconnect();
        delete c;
    }
    close(sockFd);
    clients.clear();
    if (closeCallback != nullptr) {
        closeCallback->call();
    }
}

void Server::clientDisconnected(Client* c) {
    clients.erase(c);
    epollController->removeListener(c);
}

void Server::triggerIn() {
    printf("Client connecting");
    int clientFd = accept(sockFd, nullptr, nullptr);
    if (clientFd == -1) {
        perror("accept failed");
        throw new ConnectException();
    }
    Client* client = new Client(clientFd);
    epollController->addListener(client);
    clients.insert(client);
    client->onDisconnection(new ServerClientDisconnectionCallback(this, client));
    if (clientCallback != nullptr) {
        clientCallback->call(new Client(clientFd));
    }
}

void Server::error() {
    throw new ConnectException();
}