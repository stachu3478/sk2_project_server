#include "EpollController.h"

using namespace std;
using namespace chrono;

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
    auto now = system_clock::now();
    auto stopTime = now + milliseconds(miliseconds);
    while(!shouldClose && stopTime > (now = system_clock::now())) {
        epoll_event* evts = events.data();
        int nFds = epoll_wait(fd, evts, events.size(), duration_cast<milliseconds>(stopTime - now).count());
        if (nFds == -1) {
            if (errno == EINTR) printf("EINTR received, stopping\n");
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
        closeCallback();
    }
}

void EpollController::close(function<void(void)> callback) {
    closeCallback = callback;
    shouldClose = true;
}