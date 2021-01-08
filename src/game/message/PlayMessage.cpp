#include "PlayMessage.h"

PlayMessage::~PlayMessage() {}

void PlayMessage::readBuffer(std::stringbuf* buffer) {
    int bytesToRead = buffer->in_avail();
    if (bytesToRead == 0) return;
    if (!lengthRead) {
        nicknameLength = buffer->sbumpc();
        bytesToRead--;
    }
    if (bytesToRead > nicknameLength - nickname.length()) bytesToRead = nicknameLength - nickname.length();
    if (bytesToRead == 0) return;
    char* buff = new char[bytesToRead];
    buffer->sgetn(buff, bytesToRead);
    nickname += buff;
}