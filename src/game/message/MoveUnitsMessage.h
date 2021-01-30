#pragma once

#include <functional>
#include "../../net/Buffer.h"
#include "../../net/Message.h"
#include "GameMessage.h"
#include "messageHelper.h"

class MoveUnitsMessage : public GameMessage {
    public:
        MoveUnitsMessage(std::function<void(MoveUnitsMessage*)> cb, int maxBatchSize);
        virtual ~MoveUnitsMessage();

        int* getUnitIds() { return unitIds; };
        int getTargetX() { return targetX; };
        int getTargetY() { return targetY; };
        int getUnitCount() { return unitCount; };

        void readBuffer(Buffer* buffer);
        bool isComplete() { return complete; };
        void receive() { if (!ignored) callback(this); delete this; };
    private:
        std::function<void(MoveUnitsMessage*)> callback;
        int* unitIds;
        bool complete = false;
        bool lengthRead = false;
        int targetX;
        int targetY;
        int unitCountToRead;
        int unitCount;
        int maxBatchSize;
};