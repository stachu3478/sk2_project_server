#include "EpollController.h"

EpollController::EpollController() {
    fd = epoll_create1(0);
}

void EpollController::addListener(EpollListener* l) {
    epoll_event e {};
    e.events = EPOLLIN;
    e.data.ptr = l;
    epoll_ctl(fd, EPOLL_CTL_ADD, l->getFd(), &e);
}

void EpollController::removeListener(EpollListener* l) {
    epoll_ctl(fd, EPOLL_CTL_DEL, l->getFd(), nullptr);
}

void EpollController::listen(int miliseconds) {
    shouldClose = false;
    while(!shouldClose) {
        epoll_event* evts = events.data();
        int nFds = epoll_wait(fd, evts, events.size(), miliseconds);
        if (nFds == -1) {
            perror("epoll_wait");
            throw new PollingError();
        }
        for (int i = 0; i < nFds; i++) {
            EpollListener* l = (EpollListener*)evts[i].data.ptr;
            if (evts[i].events & EPOLLHUP) {
                printf("SIGINT received, stopping\n");
            } else if (evts[i].events & EPOLLERR) { //error
                perror("Epoll event error\n");
                l->error(); // debug purposes
            } else {
                if (evts[i].events & EPOLLIN) l->triggerIn();
                else if (evts[i].events & EPOLLOUT) l->triggerOut();
            }
        }
    };
    if (closeCallback != nullptr) {
        closeCallback->call();
    }
}

void EpollController::close() {
    shouldClose = true;
}