#pragma once

#include "Client.h"

class ClientCallback {
    public:
        virtual void call(Client* client) = 0;
};