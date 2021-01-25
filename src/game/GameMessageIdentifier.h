#pragma once

#include <sstream>
#include <exception>
#include <functional>
#include "../net/Buffer.h"
#include "../net/MessageIdentifier.h"
#include "../net/Message.h"
#include "./message/PlayMessage.h"
#include "./message/MoveUnitsMessage.h"
#include "./message/AttackUnitsMessage.h"
#include "MessageFilter.h"
#include "Player.h"

class InvalidMessageError : public std::exception {};

class GameMessageIdentifier : public MessageIdentifier {
    public:
        GameMessageIdentifier(Player* p) { player = p; };
        virtual ~GameMessageIdentifier();

        void setMessageFilter(MessageFilter* f) { filter = f; };
        void onPlay(std::function<void(PlayMessage*)> cb) { this->playCallback = cb; };
        void onMoveUnits(std::function<void(MoveUnitsMessage*)> cb) { this->moveUnitsCallback = cb; };
        void onAttackUnits(std::function<void(AttackUnitsMessage*)> cb) { this->attackUnitsCallback = cb; };

        void setUnitBatchSize(int size) { maxUnitBatchSize = size; };

        Message* createMessage(Buffer* buffer);
    private:
        std::function<void(PlayMessage*)> playCallback;
        std::function<void(MoveUnitsMessage*)> moveUnitsCallback;
        std::function<void(AttackUnitsMessage*)> attackUnitsCallback;
        int maxUnitBatchSize = 0;
        MessageFilter* filter;
        Player* player;
};