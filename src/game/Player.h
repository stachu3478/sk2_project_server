#pragma once

#include <string>
#include "message/KickMessage.h"
#include "../net/Client.h"

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

        // Message handles: TODO: implement all required
        void setNickname(std::string nick) { nickname = nick; };
        std::string getNickname() { return nickname; };
    private:
        std::string nickname;
        Client* client;
        bool ill;
        int ownerId;
};