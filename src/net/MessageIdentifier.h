#include <unistd.h>
#include <sstream>
#include <exception>

class MessageReadError : public std::exception {};

class MessageIdentifier {
    public:
        MessageIdentifier(int messageFd) { fd = messageFd; buffer = new std::stringbuf(); };
        virtual ~MessageIdentifier();
        void onMessage();
        void readMessages();
    protected:
        void createMessages();
    private:
        int fd;
        char buff[1024];
        std::stringbuf* buffer;
};