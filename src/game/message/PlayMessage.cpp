#include "PlayMessage.h"

PlayMessage::PlayMessage(std::function<void(PlayMessage*)> cb)  {
    this->callback = cb;
}

PlayMessage::~PlayMessage() {}

void PlayMessage::readBuffer(Buffer* buffer) {
    int bytesToRead = buffer->in_avail();
    if (bytesToRead == 0) return;
    if (!lengthRead) {
        nicknameLengthToRead = buffer->sbumpc();
        lengthRead = true;
    }
    if (buffer->in_avail() < nicknameLengthToRead) {
        return;
    }
    char* buff = buffer->sgetn(nicknameLengthToRead);
    char* safeNickname = new char[nicknameLengthToRead + 1];
    safeNickname[nicknameLengthToRead] = '\0';
    for (int i = 0; i < nicknameLengthToRead; i++) safeNickname[i] = buff[i];
    nickname += safeNickname;
    delete[] safeNickname;
    complete = true;
}