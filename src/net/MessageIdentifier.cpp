#include "MessageIdentifier.h"

MessageIdentifier::MessageIdentifier() {
    
}

MessageIdentifier::~MessageIdentifier() {}

void MessageIdentifier::readMessages() {
    if (!bufferInitialized) {
        bufferInitialized = true;
        buffer = new std::stringbuf();
    }
    int charsRead;
    do {
        charsRead = read(fd, &buff, 1024);
        if (charsRead == -1 && errno != EAGAIN) {
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
        lastMessage->readBuffer(buffer); // FIXME: Sometimes segmentation fault
        if (lastMessage->isComplete()) {
            lastMessage->receive();
            lastMessage = createMessage(buffer);
        } else break;
    };
    if (buffer->in_avail() == 0) {
        bufferInitialized = false;
        delete buffer; // clear buffer
    }
}