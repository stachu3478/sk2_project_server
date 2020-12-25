#pragma once

#include <unistd.h>
#include "../events/EpollListener.h"
#include "./ClientDisconnectionCallback.h"
#include "./MessageIdentifier.h"
#include "./MessageCallback.h"
#include "./MessageWriter.h"
#include "./MessageOut.h"

class Client : public EpollListener {
    public:
        Client(int fd);
        virtual ~Client();

        void disconnect();
        void setMessageIdentifier(MessageIdentifier* i);
        void onDisconnection(ClientDisconnectionCallback* cb);
        void onMessage(MessageCallback* cb);
        void emit(MessageOut* m);

        int getFd();
        void triggerIn();
        void triggerOut();
        void error();
    private:
        int fd;
        MessageIdentifier* messageIdentifier;
        MessageWriter* messageWriter;
        MessageCallback* messageCallback;
        ClientDisconnectionCallback* disconnectionCallback;
};