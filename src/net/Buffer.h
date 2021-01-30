#pragma once

#include "exception"

// POOR YOU, std::stringbuf!
class Buffer {
    public:
        Buffer(){  };
        virtual ~Buffer(){ delete[] ptr; };

        int in_avail();
        char sbumpc();
        char* sgetn(int count);
        void sputn(char* b, int count);
    private:
        char* current = new char[1];
        int avail = 0;
        char* ptr = current;
};
