#include "MessageWriter.h"

MessageWriter::MessageWriter(int fd) {
    printf("yyyy?\n");
    this->fd = fd;
    printf("yyyy?\n");
}

MessageWriter::~MessageWriter() {}

void MessageWriter::emit(MessageOut* m) {
    std::string messageString = m->serialize();
    buffer.sputn(messageString.c_str(), messageString.size());
}

void MessageWriter::writeMessages() {
    int bytesToWrite = buffer.in_avail();
    char* buff = new char[bytesToWrite];
    buffer.sgetn(buff, bytesToWrite);
    printf("Message emitting\n");
    int written = 0;
    int currentWritten;
    do {
        currentWritten = write(fd, buff, bytesToWrite);
        if (currentWritten == -1) {
            perror("write");
            currentWritten = 0;
        }
        written += currentWritten;
    } while (bytesToWrite > written && currentWritten > 0);
    printf("Message emitted or at least some part of it\n");
    for (; written < bytesToWrite; written++) {
        buffer.sungetc();
    }
    delete buff;
}