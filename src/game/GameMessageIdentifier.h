#pragma once

#include <sstream>
#include <exception>
#include <functional>
#include "../net/Buffer.h"
#include "../net/MessageIdentifier.h"
#include "../net/Message.h"
#include "./message/SimpleMessage.h"
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
        void onLeaveGame(std::function<void(SimpleMessage*)> cb) { this->leaveGameCallback = cb; };
        void onChangeGame(std::function<void(SimpleMessage*)> cb) { this->changeGameCallback = cb; };

        void setUnitBatchSize(int size) { maxUnitBatchSize = size; };

        Message* createMessage(Buffer* buffer);
    private:
        std::function<void(PlayMessage*)> playCallback;
        std::function<void(MoveUnitsMessage*)> moveUnitsCallback;
        std::function<void(AttackUnitsMessage*)> attackUnitsCallback;
        std::function<void(SimpleMessage*)> leaveGameCallback;
        std::function<void(SimpleMessage*)> changeGameCallback;
        int maxUnitBatchSize = 0;
        MessageFilter* filter;
        Player* player;
};