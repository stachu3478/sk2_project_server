#pragma once

#include <sstream>
#include <exception>
#include <functional>
#include "../net/MessageIdentifier.h"
#include "../net/Message.h"
#include "./message/PlayMessage.h"
#include "MessageFilter.h"
#include "Player.h"

class InvalidMessageError : public std::exception {};

class GameMessageIdentifier : public MessageIdentifier {
    public:
        GameMessageIdentifier(Player* p) { player = p; };
        virtual ~GameMessageIdentifier();

        void setMessageFilter(MessageFilter* f) { filter = f; };
        void onPlay(std::function<void(PlayMessage*)> cb) { this->playCallback = cb; };

        Message* createMessage(std::stringbuf* buffer);
    private:
        std::function<void(PlayMessage*)> playCallback;
        MessageFilter* filter;
        Player* player;
};