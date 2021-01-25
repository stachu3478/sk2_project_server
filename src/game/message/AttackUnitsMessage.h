#pragma once

#include "../../net/Buffer.h"
#include "GameMessage.h"
#include "messageHelper.h"

class AttackUnitsMessage : public GameMessage {
    public:
        AttackUnitsMessage(std::function<void(AttackUnitsMessage*)> cb, int maxBatchSize);
        virtual ~AttackUnitsMessage();

        int* getUnitIds() { return unitIds; };
        int getTargetUnitId() { return targetUnitId; };
        int getUnitCount() { return unitCount; };

        void readBuffer(Buffer* buffer);
        bool isComplete() { return complete; };
        void receive() { if (!ignored) callback(this); };
    private:
        std::function<void(AttackUnitsMessage*)> callback;
        int* unitIds;
        bool complete = false;
        bool lengthRead = false;
        int targetUnitId;
        int unitCountToRead;
        int unitCount;
        int maxBatchSize;
};