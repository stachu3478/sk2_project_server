#include "EpollController.h"

EpollController::EpollController() {
    fd = epoll_create1(0);
}

void EpollController::addListener(EpollListener* l) {
    epoll_event e {};
    e.events = EPOLLIN;
    e.data.ptr = l;
    epoll_ctl(fd, EPOLL_CTL_ADD, l->getFd(), &e);
    printf("ctl added\n");
}

void EpollController::removeListener(EpollListener* l) {
    epoll_ctl(fd, EPOLL_CTL_DEL, l->getFd(), nullptr);
    printf("ctl removed\n");
}

void EpollController::listen(int miliseconds) {
    auto stopTime = std::chrono::system_clock::now() + std::chrono::milliseconds(miliseconds);
    while(!shouldClose && stopTime > std::chrono::system_clock::now()) {
        epoll_event* evts = events.data();
        int nFds = epoll_wait(fd, evts, events.size(), std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - std::chrono::system_clock::now()).count());
        if (nFds == -1) {
            if (errno == EINTR) printf("SIGINT received, stopping\n");
            else {
                perror("epoll_wait");
                throw new PollingError();
            }
            return;
        }
        for (int i = 0; i < nFds; i++) {
            EpollListener* l = (EpollListener*)evts[i].data.ptr;
            if (evts[i].events & EPOLLHUP) {
                l->error();
            } else if (evts[i].events & EPOLLERR) { //error
                perror("Epoll event error\n");
                l->error(); // debug purposes
            } else {
                if (evts[i].events & EPOLLIN) l->triggerIn();
                else if (evts[i].events & EPOLLOUT) l->triggerOut();
            }
        }
    };
    if (shouldClose) { // FIXME: Invalid use of member function
        printf("Polling closed\n");
        closeCallback();
    }
}

void EpollController::close(std::function<void(void)> callback) {
    closeCallback = callback;
    shouldClose = true;
}