#include "PlayMessage.h"

PlayMessage::~PlayMessage() {}

void PlayMessage::readBuffer(std::stringbuf* buffer) {
    int bytesToRead = buffer->in_avail();
    if (bytesToRead == 0) return;
    if (!lengthRead) {
        nicknameLengthToRead = buffer->sbumpc();
        bytesToRead--;
        lengthRead = true;
    }
    if (bytesToRead > nicknameLengthToRead) {
        bytesToRead = nicknameLengthToRead;
    }
    if (bytesToRead == 0) return;
    nicknameLengthToRead -= bytesToRead;
    char* buff = new char[bytesToRead];
    buffer->sgetn(buff, bytesToRead);
    nickname += buff;
}