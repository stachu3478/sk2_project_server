#include "MessageIdentifier.h"

MessageIdentifier::MessageIdentifier(int fd) {
    this->fd = fd;
    buffer = new std::stringbuf();
}

MessageIdentifier::~MessageIdentifier() {}

void MessageIdentifier::onMessage(MessageCallback* cb) {
    callback = cb;
}

void MessageIdentifier::readMessages() {
    int charsRead;
    do {
        charsRead = read(fd, buff, 1024);
        if (charsRead == -1) {
            perror("Message read error");
            throw new MessageReadError();
        }
        buffer->sputn(buff, charsRead);
    } while (charsRead > 0);
    createMessages();
}

void MessageIdentifier::createMessages() {
    if (lastMessage == nullptr) {
        lastMessage = createMessage(buffer);
    }
    do {
        lastMessage->readBuffer(buffer);
        if (lastMessage->isComplete()) {
            if (callback != nullptr) {
                callback->call(lastMessage);
            }
            lastMessage = createMessage(buffer);
        } else break;
    } while (1);
}