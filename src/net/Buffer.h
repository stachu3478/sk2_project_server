#pragma once

#include "exception"
#include "string.h"
#include "bits/stdc++.h"

// Buffer which limit is only the memory allocation
class Buffer {
    public:
        Buffer(){  };
        Buffer(char* data, int count){ sputn(data, count); };
        virtual ~Buffer(){ delete[] ptr; };

        int in_avail();
        char sbumpc();
        char* sgetn(int count, bool terminated = false);
        char* data() { return current; };
        void sputn(char* b, int count);
        void sputn(const char b[], int count) { sputn((char*)b, count); };
    private:
        char* current = new char[1];
        int avail = 0;
        char* ptr = current;
};
