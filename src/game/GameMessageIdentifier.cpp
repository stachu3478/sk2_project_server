#include "GameMessageIdentifier.h"

GameMessageIdentifier::~GameMessageIdentifier() {}

Message* GameMessageIdentifier::createMessage(Buffer* buffer) {
    if (buffer->in_avail() == 0) return nullptr;
    char messageType = buffer->sbumpc();
    GameMessage* m = nullptr;
    if (messageType == 0 && playCallback != nullptr) m = new PlayMessage(this->playCallback);
    else if (messageType == 2 && moveUnitsCallback != nullptr) m = new MoveUnitsMessage(this->moveUnitsCallback, maxUnitBatchSize);
    else if (messageType == 3 && attackUnitsCallback != nullptr) m = new AttackUnitsMessage(this->attackUnitsCallback, maxUnitBatchSize);
    else if (messageType == 4 && leaveGameCallback != nullptr) m = new SimpleMessage(this->leaveGameCallback);
    else if (messageType == 5 && changeGameCallback != nullptr) m = new SimpleMessage(this->changeGameCallback);
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