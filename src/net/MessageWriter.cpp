#include "MessageWriter.h"

MessageWriter::MessageWriter(int fd) {
    this->fd = fd;
}

MessageWriter::~MessageWriter() {}

void MessageWriter::emit(MessageOut* m) {
    char* messageString = m->serialize();
    buffer.sputn(messageString, m->length());
}

void MessageWriter::writeMessages() {
    int currentWritten;
    do {
        currentWritten = write(fd, buffer.data(), buffer.in_avail());
        if (currentWritten == -1) {
            perror("write");
        } else if (currentWritten > 0) {
            // printf("%d bytes written\n", currentWritten);
            buffer.sgetn(currentWritten);
        }
    } while (buffer.in_avail() > 0 && currentWritten > 0);
}