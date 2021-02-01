#include "Buffer.h"

int Buffer::in_avail() {
    return avail;
}

char Buffer::sbumpc() {
    if (in_avail() < 1) throw this;
    char c = current[0];
    current = current + 1;
    avail--;
    return c;
}

// Note: Need to handle output data memory while chosing terminated
char* Buffer::sgetn(int count, bool terminated) {
    if (in_avail() < count) throw this;
    char* c;
    if (terminated) {
        c = new char[count + 1];
        c[count] = '\0';
        for (int i = 0; i < count; i++) {
            c[i] = current[i];
        }
    } else c = current;
    current = current + count;
    avail -= count;
    return c;
}

void Buffer::sputn(char* b, int count) {
    if (count <= 0) return;
    char* newBuff = new char[avail + count];
    for (int i = 0; i < avail; i++) {
        newBuff[i] = current[i];
    }
    for (int i = avail, j = 0; i < avail + count; i++, j++) {
        newBuff[i] = b[j];
    }
    delete[] ptr;
    ptr = current = newBuff;
    avail += count;
}
