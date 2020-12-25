#include "MessageIdentifier.h"

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
}