#include "ServerCloseCallback.h"

ServerCloseCallback::ServerCloseCallback() {}

ServerCloseCallback::~ServerCloseCallback() {}

void ServerCloseCallback::call() {
    throw this;
}