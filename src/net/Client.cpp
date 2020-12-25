#include "Client.h"

Client::Client(int fd) {
    this->fd = fd;
    this->messageWriter = new MessageWriter(fd);
}

Client::~Client() {}

void Client::onDisconnection(ClientDisconnectionCallback* c) {
    disconnectionCallback = c;
}

void Client::onMessage(MessageCallback* c) {
    messageIdentifier->onMessage(c);
}

void Client::disconnect() {
    close(fd);
    if (disconnectionCallback != nullptr) {
        disconnectionCallback->call();
    }
}

void Client::emit(MessageOut* m) {
    messageWriter->emit(m);
    messageWriter->writeMessages(); // TODO: handle unavailable writes
}

int Client::getFd() { return fd; }

void Client::triggerIn() {
    messageIdentifier->readMessages();
}

void Client::triggerOut() {
    messageIdentifier->readMessages();
}

void Client::error() {
    disconnect();
}