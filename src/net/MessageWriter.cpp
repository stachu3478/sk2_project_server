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
    char buff[1];
    for (int i = 0; i < bytesToWrite; i++) {
        buff[0] = buffer->sbumpc();
        if (write(fd, buff, 1) == -1) {
            buffer->sungetc();
            break;
        }
    }
}