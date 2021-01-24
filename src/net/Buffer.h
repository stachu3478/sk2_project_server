#pragma once

#include "exception"

// FUCK YOU, std::stringbuf!
class Buffer {
    public:
        Buffer(){};
        Buffer(char* b, int count){ sputn(b, count); };
        virtual ~Buffer(){ if (next != nullptr) delete next; };

        int in_avail();
        char sbumpc();
        char* sgetn(int count);
        void sputn(char* b, int count);
    private:
        void trainBack();
        char* current;
        int avail = 0;
        Buffer* next = nullptr;
        bool hasNext = false;
};