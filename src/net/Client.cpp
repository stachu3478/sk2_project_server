#include "Client.h"

Client::Client(int fd) {
    this->fd = fd;
    this->messageWriter = new MessageWriter(fd);
}

Client::~Client() {}

void Client::disconnect() {
    close(fd);
    if (disconnectionCallback != nullptr) {
        disconnectionCallback->call();
    }
}

void Client::setMessageIdentifier(MessageIdentifier* i) {
    messageIdentifier = i;
    messageIdentifier->setFd(fd);
}

void Client::onDisconnection(ClientDisconnectionCallback* c) {
    disconnectionCallback = c;
}

void Client::onMessage(MessageCallback* c) {
    messageIdentifier->onMessage(c);
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
    messageWriter->writeMessages();
}

void Client::error() {
    disconnect();
}