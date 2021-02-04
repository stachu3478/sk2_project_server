#pragma once

#include <unistd.h>
#include <functional>
#include <memory>
#include "Client.h"
#include "../events/EpollListener.h"
#include "./MessageIdentifier.h"
#include "./MessageWriter.h"
#include "./MessageOut.h"

class NettyClient : public Client, public EpollListener  {
    public:
        NettyClient(int fd) : messageWriter{fd} { this->fd = fd; };
        virtual ~NettyClient() {};

        void disconnect();
        void setMessageIdentifier(MessageIdentifier* i);
        MessageIdentifier* getMessageIdentifier() { return messageIdentifier; };
        void emit(MessageOut* m) { messageWriter.emit(m); };
        void flush() { messageWriter.writeMessages(); }; // TODO: handle unavailable writes
        bool isOffline() { return fd < 0; };

        int getFd() { return fd; };
        void triggerIn();
        void triggerOut() { messageWriter.writeMessages(); };
        void error() { disconnect(); };
        void closed() { disconnect(); };
    private:
        int fd;
        MessageIdentifier* messageIdentifier;
        MessageWriter messageWriter;
};

typedef std::shared_ptr<NettyClient> NettyClientPtr;
