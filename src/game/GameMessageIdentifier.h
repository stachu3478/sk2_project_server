#pragma once

#include <sstream>
#include <exception>
#include "../net/MessageIdentifier.h"
#include "../net/Message.h"
#include "./message/PlayMessage.h"
#include "MessageFilter.h"
#include "Player.h"

class InvalidMessageError : public std::exception {};

class GameMessageIdentifier : public MessageIdentifier {
    public:
        GameMessageIdentifier(Player* p) { printf("msgi constructor called\n"); player = p; };
        virtual ~GameMessageIdentifier();

        void setMessageFilter(MessageFilter* f) { filter = f; };

        Message* createMessage(std::stringbuf* buffer);
    private:
        MessageFilter* filter;
        Player* player;
};