#include "MoveUnitsMessage.h"

MoveUnitsMessage::MoveUnitsMessage(std::function<void(MoveUnitsMessage*)> cb, int maxBatchSize)  {
    lengthRead = false;
    this->callback = cb;
    this->maxBatchSize = maxBatchSize;
}

MoveUnitsMessage::~MoveUnitsMessage() {
    delete unitIds;
}

void MoveUnitsMessage::readBuffer(Buffer* buffer) {
    int bytesAvailable = buffer->in_avail();
    if (!lengthRead) {
        if ((bytesAvailable -= 12) < 0) return;
        targetX = readInteger(buffer);
        targetY = readInteger(buffer);
        unitCount = unitCountToRead = readInteger(buffer);
        if (unitCountToRead > maxBatchSize || unitCountToRead < 1) { // No way guy TODO: make better error callback
            unitCount = 0;
            unitIds = new int[0];
            complete = true;
            return;
        }
        unitIds = new int[unitCountToRead];
        lengthRead = true;
    }
    if (bytesAvailable < unitCountToRead * 4) {
        return;
    }
    while (unitCountToRead > 0) {
        unitIds[--unitCountToRead] = readInteger(buffer);
    }
    complete = true;
}