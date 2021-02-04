#include "NettyClient.h"

void NettyClient::disconnect() {
    close(fd);
    fd = -1;
    disconnectionCallback();
}

void NettyClient::setMessageIdentifier(MessageIdentifier* i) {
    messageIdentifier = i;
    messageIdentifier->setFd(fd);
}

void NettyClient::triggerIn() {
    if (messageIdentifier->readMessages() == 0) disconnect();
}
