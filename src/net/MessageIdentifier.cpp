#include "MessageIdentifier.h"

int MessageIdentifier::readMessages() {
    int charsRead;
    int totalRead = 0;
    do {
        charsRead = read(fd, &buff, 1024);
        if (charsRead == -1) {
            if (errno != EWOULDBLOCK) {
                perror("Message read error");
                throw new MessageReadError();
            }
        } else if (charsRead > 0) {
            totalRead += charsRead;
            buffer.sputn(buff, charsRead);
            // printf("%d bytes read\n", charsRead);
        }
    } while (charsRead > 0);
    createMessages();
    return totalRead;
}

void MessageIdentifier::createMessages() {
    if (lastMessage == nullptr) {
        lastMessage = createMessage(&buffer);
    }
    while (lastMessage != nullptr) {
        lastMessage->readBuffer(&buffer); // FIXME: Sometimes segmentation fault
        if (lastMessage->isComplete()) {
            lastMessage->receive();
            lastMessage = createMessage(&buffer);
        } else break;
    };
}