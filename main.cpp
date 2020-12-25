#include <iostream>
#include <signal.h>
#include "src/net/Server.h"
#include "src/events/EpollController.h"
#include "src/net/ServerCloseCallback.h"

class ShutdownCallback : public ServerCloseCallback {
    public:
        void call() { exit(0); };
};

Server* server;
void ctrl_c(int) {
    std::cout << "Server shutting down...\n";
    server->onShutdown(new ShutdownCallback());
    server->shutdown();
}

int main(int, char**) {
    std::cout << "Hello, world!\n";
    EpollController* epollController = new EpollController();

    signal(SIGINT, ctrl_c);
    signal(SIGPIPE, SIG_IGN);

    server = new Server();
    server->setEpollController(epollController);
    server->listenAt(34780);
}
