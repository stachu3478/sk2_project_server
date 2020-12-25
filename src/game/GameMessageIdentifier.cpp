#include "GameMessageIdentifier.h"

GameMessageIdentifier::~GameMessageIdentifier() {}

Message* GameMessageIdentifier::createMessage(std::stringbuf* buffer) {
    if (buffer->in_avail() == 0) return nullptr;
    char messageType = buffer->sbumpc();
    GameMessage* m;
    if (messageType == 0) m = new PlayMessage();
    // else if blablabla
    // ... more message type verifies
    else throw new InvalidMessageError();

    m->setPlayer(player);
    if (filter->shouldIgnore(messageType)) m->ignore();
    return m;
}