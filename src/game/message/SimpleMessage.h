#pragma once

#include "../../net/Buffer.h"
#include "GameMessage.h"

class SimpleMessage : public GameMessage {
    public:
        SimpleMessage(std::function<void(SimpleMessage*)> cb) { this->callback = cb; };
        virtual ~SimpleMessage() {};

        void readBuffer(Buffer* _) { _->in_avail(); };
        bool isComplete() { return true; };
        void receive() { if (!ignored) callback(this); };
    private:
        std::function<void(SimpleMessage*)> callback;
};
