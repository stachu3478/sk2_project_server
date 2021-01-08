#pragma once

#include <sstream>
#include <algorithm>
#include "../../net/Message.h"
#include "GameMessage.h"

class PlayMessage : public GameMessage {
    public:
        PlayMessage() { lengthRead = false; };
        virtual ~PlayMessage();

        std::string getNickname() { return nickname; };

        void readBuffer(std::stringbuf* buffer);
        bool isComplete() { return nicknameLength == (char)nickname.size(); };
        void receive() { if (!ignored) player->play(nickname); };
    private:
        std::string nickname;
        char nicknameLength;
        bool lengthRead;
};