#include "Client.h"

Client::Client(int fd) {
    this->fd = fd;
    this->messageWriter = new MessageWriter(fd);
}

Client::~Client() {
    delete messageIdentifier;
    delete messageWriter;
}

void Client::disconnect() {
    close(fd);
    fd = -1;
    disconnectionCallback();
}

void Client::setMessageIdentifier(MessageIdentifier* i) {
    messageIdentifier = i;
    messageIdentifier->setFd(fd);
}

void Client::onDisconnection(std::function<void()> c) {
    disconnectionCallback = c;
}

void Client::emit(MessageOut* m) {
    messageWriter->emit(m);
    messageWriter->writeMessages(); // TODO: handle unavailable writes
}

int Client::getFd() { return fd; }

void Client::triggerIn() {
    if (messageIdentifier->readMessages() == 0) disconnect();
}

void Client::triggerOut() {
    messageWriter->writeMessages();
}

void Client::error() {
    disconnect();
}