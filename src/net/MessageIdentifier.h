#include <unistd.h>
#include <sstream>
#include <exception>
#include "Message.h"
#include "MessageCallback.h"

class MessageReadError : public std::exception {};

class MessageIdentifier {
    public:
        MessageIdentifier(int fd);
        virtual ~MessageIdentifier();

        void onMessage(MessageCallback* cb);
        void readMessages();
    protected:
        virtual Message* createMessage(std::stringbuf* buffer) = 0;
    private:
        void createMessages();
        Message* lastMessage;
        MessageCallback* callback;
        int fd;
        char buff[1024];
        std::stringbuf* buffer;
};