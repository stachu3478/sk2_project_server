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
        epoll_wait(fd, events.data(), 32, miliseconds);
        for (epoll_event e : events) {
            EpollListener* l = (EpollListener*)e.data.ptr;
            if (e.events & EPOLLHUP) {
                write(1, "SIGINT received, stopping", 26);
            } else if (e.events & EPOLLERR) { //error
                perror("Epoll event error");
                if (e.data.ptr != nullptr) l->error();
            } else {
                if (e.events & EPOLLIN) l->triggerIn();
                if (e.events & EPOLLOUT) l->triggerOut();
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