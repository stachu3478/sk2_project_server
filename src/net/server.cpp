#include "server.h"

Server::Server() {
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
}

void Server::listen(int port) {
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
}