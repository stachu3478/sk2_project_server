#pragma once

class Client {
    public:
        Client(int fd) { this->fd = fd; };
    void disconnect() { close(fd); };
    private:
        int fd;
};