#pragma once

#include <string>
#include <unordered_map>
#include "message/KickMessage.h"
#include "../net/Client.h"
#include "Unit.h"

class Player {
    public:
        Player(Client* c);
        virtual ~Player();

        Client* getClient() { return client; };
        
        void kick(const char* reason);
        bool isIll() { return ill; };
        void emit(MessageOut* m);
        void setOwnerId(int id) { this->ownerId = id; };
        int getOwnerId() { return this->ownerId; };
        void setIngame(bool ingame);

        void addUnit(Unit* unit) { this->units.insert(std::pair<int, Unit*>(unit->getId(), unit)); };
        void removeUnit(Unit* unit) { removeUnit(unit->getId()); };
        void removeUnit(int id) { this->units.erase(id); };
        std::unordered_map<int, Unit*> getUnits() { return units; };

        // Message handles: TODO: implement all required
        void setNickname(std::string nick) { nickname = nick; };
        std::string getNickname() { return nickname; };
    private:
        std::string nickname;
        Client* client;
        bool ill;
        int ownerId;
        std::unordered_map<int, Unit*> units;
};