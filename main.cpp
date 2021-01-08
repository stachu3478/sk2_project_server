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

int main(int argc, char** argv) {
    signal(SIGINT, ctrl_c);
    signal(SIGPIPE, SIG_IGN);

    server = new GameController();
    if (argc > 1) {
        server->setServerPort(atoi(argv[1]));
    }
    server->start();
}
