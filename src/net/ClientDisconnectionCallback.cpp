#include "ClientDisconnectionCallback.h"

ClientDisconnectionCallback::ClientDisconnectionCallback() {}

ClientDisconnectionCallback::~ClientDisconnectionCallback() {}

void ClientDisconnectionCallback::call() {
    throw this;
}