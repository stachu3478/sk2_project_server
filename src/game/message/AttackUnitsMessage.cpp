#include "AttackUnitsMessage.h"

AttackUnitsMessage::AttackUnitsMessage(std::function<void(AttackUnitsMessage*)> cb, int maxBatchSize)  {
    lengthRead = false;
    this->callback = cb;
    this->maxBatchSize = maxBatchSize;
}

AttackUnitsMessage::~AttackUnitsMessage() {
    delete[] unitIds;
}

void AttackUnitsMessage::readBuffer(Buffer* buffer) {
    int bytesAvailable = buffer->in_avail();
    if (!lengthRead) {
        if ((bytesAvailable -= 8) < 0) return;
        targetUnitId = readInteger(buffer);
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