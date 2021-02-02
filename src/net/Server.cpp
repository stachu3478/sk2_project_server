#include "Server.h"

using namespace std;

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
    const int one = 1;
    int optSet = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if (optSet == -1) {
        perror("setsocketopt failed");
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
    epollController.addListener(this);
    printf("Listening on *:%d\n", port);
}

void Server::shutdown(function<void(void)> callback) {
    epollController.removeListener(this);
    epollController.close([this, callback]() {
        this->closeAll();
        callback();
    });
    alive = false;
}

void Server::closeAll() {
    for (Client* c : clients) {
        c->disconnect();
        delete c;
    }
    close(sockFd);
    clients.clear();
}

void Server::clientDisconnected(Client* c) {
    clients.erase(c);
    epollController.removeListener(c);
}

void Server::triggerIn() {
    int clientFd = accept(sockFd, nullptr, nullptr);
    if (clientFd == -1) {
        perror("accept failed");
        throw new ConnectException();
    }
    int config = fcntl(clientFd, F_SETFL, O_NONBLOCK);
    if (config == -1) {
        perror("fctnl");
        throw new ConnectException();
    }
    Client* client = new Client(clientFd);
    epollController.addListener(client);
    clients.insert(client);
    client->onDisconnection([this, client]{
        this->clientDisconnected(client);
    });
    clientCallback(client);
}

void Server::error() {
    throw new ConnectException();
}
