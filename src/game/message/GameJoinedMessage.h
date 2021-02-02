#pragma once

#include <string.h>
#include <unordered_map>
#include "../Unit.h"
#include "SimpleMessageOut.h"
#include "messageHelper.h"

class GameJoinedMessage : public SimpleMessageOut {
    public:
        GameJoinedMessage(std::unordered_map<int, UnitPtr> units) { this->units = units; };
        virtual ~GameJoinedMessage();

        char* serialize();
        int length() { return 5 + units.size() * 14; };
        char getType() { return 1; }
    private:
        std::unordered_map<int, UnitPtr> units;
};