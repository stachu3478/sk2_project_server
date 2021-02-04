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
    for (NettyClientPtr c : clients) c->disconnect();
    close(sockFd);
    clients.clear();
}

void Server::clientDisconnected(NettyClientPtr c) {
    epollController.removeListener(c.get()); // Mandatory before erasing
    clients.erase(c);
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
    NettyClientPtr nettyClient {new NettyClient(clientFd)};
    ClientPtr client = dynamic_pointer_cast<Client>(nettyClient);
    epollController.addListener(nettyClient.get());
    clients.insert(nettyClient);
    client->onDisconnection([this, nettyClient]{
        this->clientDisconnected(nettyClient);
    });
    clientCallback(client);
}

void Server::error() {
    throw new ConnectException();
}
