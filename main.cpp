#include <iostream>
#include <signal.h>
#include "src/game/GameController.h"
#include "src/events/EpollController.h"

void noop(){}

GameController* server;
void ctrl_c(int) {
    server->stop(noop);
}

int main(int argc, char** argv) {
    signal(SIGABRT, ctrl_c);
    signal(SIGINT, ctrl_c);
    signal(SIGPIPE, SIG_IGN);

    GameController gameController;
    server = &gameController;
    if (argc > 1) {
        server->setServerPort(atoi(argv[1]));
    }
    server->start(); // wont stop until stop will be called externally
    return 0;
}
