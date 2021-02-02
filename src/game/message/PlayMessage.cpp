#include "PlayMessage.h"

using namespace std;

PlayMessage::PlayMessage(function<void(PlayMessage*)> cb)  {
    this->callback = cb;
}

void PlayMessage::readBuffer(Buffer* buffer) {
    int bytesToRead = buffer->in_avail();
    if (bytesToRead == 0) return;
    if (!lengthRead) {
        nicknameLengthToRead = (unsigned char)buffer->sbumpc();
        lengthRead = true;
    }
    if (buffer->in_avail() < nicknameLengthToRead) {
        return;
    }
    char* safeNickname = buffer->sgetn(nicknameLengthToRead, true);
    nickname += safeNickname;
    delete[] safeNickname;
    complete = true;
}