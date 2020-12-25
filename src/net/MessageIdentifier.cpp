#include "MessageIdentifier.h"

MessageIdentifier::MessageIdentifier() {
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
            lastMessage->receive();
            lastMessage = createMessage(buffer);
        } else break;
    } while (lastMessage != nullptr);
}