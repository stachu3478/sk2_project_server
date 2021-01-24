#include "GameMessageIdentifier.h"

GameMessageIdentifier::~GameMessageIdentifier() {}

Message* GameMessageIdentifier::createMessage(Buffer* buffer) {
    if (buffer->in_avail() == 0) return nullptr;
    char messageType = buffer->sbumpc();
    GameMessage* m = nullptr;
    if (messageType == 0) m = new PlayMessage(this->playCallback);
    else if (messageType == 2) m = new MoveUnitsMessage(this->moveUnitsCallback, maxUnitBatchSize);
    // else if blablabla
    // ... more message type verifies
    else {
        player->kick("Internal server error");
        return nullptr;
    };
    m->setPlayer(player);
    if (filter->shouldIgnore(messageType)) m->ignore();
    return m;
}