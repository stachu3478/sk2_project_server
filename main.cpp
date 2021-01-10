#include <iostream>
#include <signal.h>
#include "src/game/GameController.h"
#include "src/events/EpollController.h"

GameController* server;
void ctrl_c(int) {
    std::cout << "Server shutting down...\n";
    server->stop([](){
        exit(0);
    });
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
