#include "MessageWriter.h"

MessageWriter::MessageWriter(int fd) {
    this->fd = fd;
    this->buffer = new std::stringbuf();
}

MessageWriter::~MessageWriter() {}

void MessageWriter::emit(MessageOut* m) {
    std::string messageString = m->serialize();
    buffer->sputn(messageString.c_str(), messageString.size());
}

void MessageWriter::writeMessages() {
    int bytesToWrite = buffer->in_avail();
    char* buff = new char[bytesToWrite];
    buffer->sgetn(buff, bytesToWrite);
    int written = write(fd, buff, bytesToWrite);
    if (written == -1) written = 0;
    for (; written < bytesToWrite; written++) {
        buffer->sungetc();
    }
    delete buff;
}