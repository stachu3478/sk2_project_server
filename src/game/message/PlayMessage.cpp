#include "PlayMessage.h"

PlayMessage::~PlayMessage() {}

void PlayMessage::readBuffer(std::stringbuf* buffer) {
    int bytesToRead = buffer->in_avail();
    if (bytesToRead == 0) return;
    if (!lengthRead) {
        nicknameLength = buffer->sbumpc();
        bytesToRead--;
    }
    if (bytesToRead > nicknameLength) {
        bytesToRead = nicknameLength;
    }
    if (bytesToRead == 0) return;
    nicknameLength -= bytesToRead;
    char* buff = new char[bytesToRead];
    buffer->sgetn(buff, bytesToRead);
    nickname += buff;
}