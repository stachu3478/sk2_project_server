#include "MessageWriter.h"

MessageWriter::MessageWriter(int fd) {
    this->fd = fd;
}

MessageWriter::~MessageWriter() {}

void MessageWriter::emit(MessageOut* m) {
    char* messageString = m->serialize();
    if (bufferAllocated) { // need to rewrite buffers
        writePos -= readPos;
        char* newBuffer = new char[writePos + m->length()];
        for (int i = 0; i < writePos; i++) {
            newBuffer[i] = buffer[readPos++];
        }
        readPos = 0;
        for (int i = 0; i < m->length(); i++) {
            newBuffer[writePos++] = messageString[i];
        }
        delete buffer;
        buffer = newBuffer;
    } else {
        buffer = messageString;
        writePos = m->length();
        readPos = 0;
    }
    bufferAllocated = true;
}

void MessageWriter::writeMessages() {
    int currentWritten;
    do {
        currentWritten = write(fd, buffer + readPos, writePos - readPos);
        if (currentWritten == -1) {
            perror("write");
            currentWritten = 0;
        }
        readPos += currentWritten;
    } while (writePos - readPos > 0 && currentWritten > 0);
    if (writePos == readPos) {
        delete buffer;
        bufferAllocated = false;
    }
}