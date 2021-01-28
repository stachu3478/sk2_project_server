#pragma once

#include <unistd.h>
#include <functional>
#include "../events/EpollListener.h"
#include "./MessageIdentifier.h"
#include "./MessageWriter.h"
#include "./MessageOut.h"

class Client : public EpollListener {
    public:
        Client(int fd);
        virtual ~Client();

        void disconnect();
        void setMessageIdentifier(MessageIdentifier* i);
        MessageIdentifier* getMessageIdentifier() { return messageIdentifier; };
        void onDisconnection(std::function<void()> cb);
        void emit(MessageOut* m);

        int getFd();
        void triggerIn();
        void triggerOut();
        void error();
        void closed() { disconnect(); };
    private:
        int fd;
        MessageIdentifier* messageIdentifier;
        MessageWriter* messageWriter;
        std::function<void()> disconnectionCallback;
};