#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include "message/KickMessage.h"
#include "../net/Client.h"
#include "GameMessageIdentifier.h"
#include "Unit.h"

class Player {
    public:
        Player(Client* c);
        virtual ~Player();

        Client* getClient() { return client; };
        GameMessageIdentifier* getMessageIdentifier() { return &messageIdentifier; };
        
        bool isOffline() { return client == nullptr; };
        void kick(const char* reason);
        void emit(MessageOut* m);
        void setOwnerId(int id) { this->ownerId = id; };
        int getOwnerId() { return this->ownerId; };

        void setScore(int wynik){this->score = wynik;};
        int getScore(){return score;};
        void addScore(int add){this->score += add;};
    
        void addUnit(UnitPtr unit);
        void removeUnit(UnitPtr unit) { removeUnit(unit->getId()); };
        void removeUnit(int id) { this->units.erase(id); };
        std::unordered_map<int, UnitPtr> getUnits() { return units; };
        void clearUnits() { units.clear(); };
        int getUnitCount() { return units.size(); };

        // Message handles: TODO: implement all required
        void setNickname(std::string nick) { nickname = nick; };
        std::string getNickname() { return nickname; };
    private:
        GameMessageIdentifier messageIdentifier;
        std::string nickname;
        Client* client;
        int ownerId;
        int score;
        std::unordered_map<int, UnitPtr> units;
};

typedef std::shared_ptr<Player> PlayerPtr;