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

        // Message handles: TODO: implement all required
        void play(std::string nick) { nickname = nick; printf("%s joined the game\n", nick.c_str()); };
    private:
        std::string nickname;
        Client* client;
        bool ill;
};