#pragma once

#include <string>
#include "../net/Client.h"

class Player {
    public:
        Player(Client* c) { client = c; };
        virtual ~Player();

        Client* getClient() { return client; };
        

        // Message handles: TODO: implement all required
        void play(std::string nick) { nickname = nick; };
    private:
        std::string nickname;
        Client* client;
};