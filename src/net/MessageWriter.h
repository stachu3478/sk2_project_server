#include <unistd.h>
#include <sstream>
#include "Buffer.h"
#include "MessageOut.h"

class MessageWriter {
    public:
        MessageWriter(int fd);
        virtual ~MessageWriter();

        void emit(MessageOut* m);
        void writeMessages();
    private:
        int fd;
        Buffer buffer;
};