#include "Client.h"

Client::Client(int fd) {
    printf("yyyy?\n");
    this->fd = fd;
    printf("yyyy?\n");
    this->messageWriter = new MessageWriter(fd);
    printf("Ich bin eine neue Client\n");
}

Client::~Client() {
}

void Client::disconnect() {
    close(fd);
    disconnectionCallback();
}

void Client::setMessageIdentifier(MessageIdentifier* i) {
    messageIdentifier = i;
    messageIdentifier->setFd(fd);
    printf("Message identifier set %d\n", fd);
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
    messageIdentifier->readMessages();
}

void Client::triggerOut() {
    messageWriter->writeMessages();
}

void Client::error() {
    disconnect();
}