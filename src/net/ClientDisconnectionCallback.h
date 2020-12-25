#pragma once

class ClientDisconnectionCallback {
    public:
        ClientDisconnectionCallback();
        virtual ~ClientDisconnectionCallback();
        virtual void call();
};