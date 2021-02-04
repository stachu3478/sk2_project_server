#include "GameMessageIdentifier.h"

Message* GameMessageIdentifier::createMessage(Buffer* buffer) {
    if (buffer->in_avail() == 0) return nullptr;
    char messageType = buffer->sbumpc();
    GameMessage* m = nullptr;
    if (messageType == GMessage::PLAY && playCallback != nullptr) m = new PlayMessage(this->playCallback);
    else if (messageType == GMessage::MOVE_UNITS && moveUnitsCallback != nullptr) m = new MoveUnitsMessage(this->moveUnitsCallback, maxUnitBatchSize);
    else if (messageType == GMessage::ATTACK_UNITS && attackUnitsCallback != nullptr) m = new AttackUnitsMessage(this->attackUnitsCallback, maxUnitBatchSize);
    else if (messageType == GMessage::LEAVE_GAME && leaveGameCallback != nullptr) m = new SimpleMessage(this->leaveGameCallback);
    else if (messageType == GMessage::CHANGE_GAME && changeGameCallback != nullptr) m = new SimpleMessage(this->changeGameCallback);
    // else if blablabla
    // ... more message type verifies
    else {
        invalidMessageCallback();
        return nullptr;
    };
    if (filter(messageType)) m->ignore();
    return m;
}