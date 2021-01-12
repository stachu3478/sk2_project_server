#include <unistd.h>
#include <sstream>
#include <string>
#include "MessageOut.h"

class MessageWriter {
    public:
        MessageWriter(int fd);
        virtual ~MessageWriter();

        void emit(MessageOut* m);
        void writeMessages();
    private:
        int fd;
        std::stringbuf buffer;
};