#pragma once

#include <sstream>
#include <algorithm>
#include "../../../net/Buffer.h"
#include "GameMessage.h"

class PlayMessage : public GameMessage {
    public:
        PlayMessage(std::function<void(PlayMessage*)> cb) { this->callback = cb; };
        virtual ~PlayMessage() {};

        std::string getNickname() { return nickname; };

        void readBuffer(Buffer* buffer);
        bool isComplete() { return complete; };
        void receive() { if (!ignored) callback(this); delete this; };
    private:
        std::function<void(PlayMessage*)> callback;
        std::string nickname;
        bool complete = false;
        bool lengthRead = false;
        int nicknameLengthToRead;
};