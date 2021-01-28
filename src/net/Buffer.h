#pragma once

#include "exception"

// POOR YOU, std::stringbuf!
class Buffer {
    public:
        Buffer(){};
        Buffer(char* b, int count){ sputn(b, count); };
        virtual ~Buffer(){  };

        int in_avail();
        char sbumpc();
        char* sgetn(int count);
        void sputn(char* b, int count);
    private:
        char* current;
        int avail = 0;
};
