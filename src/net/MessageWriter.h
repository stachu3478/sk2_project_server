#include <unistd.h>
#include <sstream>
#include "MessageOut.h"

class MessageWriter {
    public:
        MessageWriter(int fd);
        virtual ~MessageWriter();

        void emit(MessageOut* m);
        void writeMessages();
    private:
        int fd;
        char* buffer;
        bool bufferAllocated = false;
        int writePos = 0;
        int readPos = 0;
};