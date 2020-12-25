#include <iostream>
#include <signal.h>
#include "src/game/GameController.h"
#include "src/events/EpollController.h"
#include "src/net/ServerCloseCallback.h"

class ShutdownCallback : public ServerCloseCallback {
    public:
        void call() { exit(0); };
};

GameController* server;
void ctrl_c(int) {
    std::cout << "Server shutting down...\n";
    server->onStopped(new ShutdownCallback());
    server->stop();
}

int main(int, char**) {
    std::cout << "Hello, world!\n";

    signal(SIGINT, ctrl_c);
    signal(SIGPIPE, SIG_IGN);

    server = new GameController();
    server->start();
}
