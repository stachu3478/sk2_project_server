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
    nickname += buff;
    complete = true;
}