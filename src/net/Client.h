#pragma once

#include <unistd.h>
#include <functional>
#include <memory>
#include "./MessageIdentifier.h"
#include "./MessageOut.h"

class Client {
    public:
        Client() {};
        virtual ~Client() {};

        virtual void disconnect() = 0;
        virtual void setMessageIdentifier(MessageIdentifier* i) = 0;
        virtual MessageIdentifier* getMessageIdentifier() = 0;
        void onDisconnection(std::function<void()> c) { disconnectionCallback = c; };
        virtual void emit(MessageOut* m) = 0;
        virtual void flush() = 0;
        virtual bool isOffline() = 0;
    protected:
        std::function<void()> disconnectionCallback;
};

typedef std::shared_ptr<Client> ClientPtr;
