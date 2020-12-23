#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>

class ConnectException : public std::exception {};

class Server {
    public:
        Server();
    private:
        void listen(int port);
        sockaddr_in addr;
        int sockFd;
};