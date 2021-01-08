#include "MessageIdentifier.h"

MessageIdentifier::MessageIdentifier() {
    buffer = new std::stringbuf();
}

MessageIdentifier::~MessageIdentifier() {}

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
    while (lastMessage != nullptr) {
        lastMessage->readBuffer(buffer);
        if (lastMessage->isComplete()) {
            lastMessage->receive();
            lastMessage = createMessage(buffer);
        } else break;
    };
    printf("Reading messages");
}