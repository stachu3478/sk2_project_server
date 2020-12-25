#include "Client.h"

Client::Client(int fd) {
    this->fd = fd;
}

Client::~Client() {}

void Client::disconnect() {
    close(fd);
    if (disconnectionCallback != nullptr) {
        disconnectionCallback->call();
    }
}