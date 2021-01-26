#include "MessageIdentifier.h"

MessageIdentifier::MessageIdentifier() {
    
}

MessageIdentifier::~MessageIdentifier() {}

void MessageIdentifier::readMessages() {
    int charsRead;
    do {
        charsRead = read(fd, &buff, 1024);
        if (charsRead == -1) {
            if (errno != EAGAIN) {
                perror("Message read error");
                throw new MessageReadError();
            }
        } else if (charsRead > 0) {
            buffer->sputn(buff, charsRead);
            printf("%d bytes read\n", charsRead);
        }
    } while (charsRead > 0);
    createMessages();
}

void MessageIdentifier::createMessages() {
    if (lastMessage == nullptr) {
        lastMessage = createMessage(buffer);
    }
    while (lastMessage != nullptr) {
        lastMessage->readBuffer(buffer); // FIXME: Sometimes segmentation fault
        if (lastMessage->isComplete()) {
            lastMessage->receive();
            lastMessage = createMessage(buffer);
        } else break;
    };
}