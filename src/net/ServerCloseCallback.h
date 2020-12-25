#pragma once

class ServerCloseCallback {
    public:
        ServerCloseCallback();
        virtual ~ServerCloseCallback();
        virtual void call();
};