#pragma once

#include <sstream>
#include <exception>
#include <functional>
#include "core/MessageFilter.h"
#include "../net/Buffer.h"
#include "../net/MessageIdentifier.h"
#include "./message/in/SimpleMessage.h"
#include "./message/in/PlayMessage.h"
#include "./message/in/MoveUnitsMessage.h"
#include "./message/in/AttackUnitsMessage.h"

class InvalidMessageError : public std::exception {};

class GameMessageIdentifier : public MessageIdentifier {
    public:
        GameMessageIdentifier() { };
        virtual ~GameMessageIdentifier() {};

        void setMessageFilter(std::function<bool(char)> f) { filter = f; };
        void onPlay(std::function<void(PlayMessage*)> cb) { this->playCallback = cb; };
        void onMoveUnits(std::function<void(MoveUnitsMessage*)> cb) { this->moveUnitsCallback = cb; };
        void onAttackUnits(std::function<void(AttackUnitsMessage*)> cb) { this->attackUnitsCallback = cb; };
        void onLeaveGame(std::function<void(SimpleMessage*)> cb) { this->leaveGameCallback = cb; };
        void onChangeGame(std::function<void(SimpleMessage*)> cb) { this->changeGameCallback = cb; };
        void onInvalidMessage(std::function<void()> cb) { this->invalidMessageCallback = cb; };

        void setUnitBatchSize(int size) { maxUnitBatchSize = size; };

        Message* createMessage(Buffer* buffer);
    private:
        std::function<void(PlayMessage*)> playCallback;
        std::function<void(MoveUnitsMessage*)> moveUnitsCallback;
        std::function<void(AttackUnitsMessage*)> attackUnitsCallback;
        std::function<void(SimpleMessage*)> leaveGameCallback;
        std::function<void(SimpleMessage*)> changeGameCallback;
        std::function<void()> invalidMessageCallback;
        int maxUnitBatchSize = 0;
        std::function<bool(char)> filter;
};