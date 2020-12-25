#pragma once

#include "Client.h"

class ClientCallback {
    public:
        virtual ~ClientCallback();
        virtual void call(Client* client);
};