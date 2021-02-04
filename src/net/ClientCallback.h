#pragma once

#include "Client.h"

class ClientCallback {
    public:
        virtual void call(ClientPtr client) = 0;
};