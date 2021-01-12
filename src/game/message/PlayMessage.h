#pragma once

#include <sstream>
#include <algorithm>
#include "../../net/Message.h"
#include "GameMessage.h"

class PlayMessage : public GameMessage {
    public:
        PlayMessage(std::function<void(PlayMessage*)> cb);
        virtual ~PlayMessage();

        std::string getNickname() { return nickname; };

        void readBuffer(std::stringbuf* buffer);
        bool isComplete() { return nicknameLengthToRead <= 0; };
        void receive() { if (!ignored) callback(this); };
    private:
        std::function<void(PlayMessage*)> callback;
        std::string nickname;
        char nicknameLengthToRead;
        bool lengthRead;
};