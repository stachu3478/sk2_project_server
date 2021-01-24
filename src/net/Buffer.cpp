#include "Buffer.h"

int Buffer::in_avail() {
    int myAvail = avail;
    if (next != nullptr) myAvail += next->in_avail();
    return myAvail;
}

char Buffer::sbumpc() {
    if (in_avail() < 1) throw this;
    if (avail < 1) return next->sbumpc();
    char c = current[0];
    current = current + 1;
    avail--;
    trainBack();
    return c;
}

char* Buffer::sgetn(int count) {
    if (in_avail() < count) throw this;
    char* b = new char[count];
    int toBeCopied = avail;
    if (count < toBeCopied) toBeCopied = count;
    for (int i = 0; i < toBeCopied; i++) {
        b[i] = current[i];
    }
    if (avail < count) {
        char* nextB = next->sgetn(count - avail);
        for (int i = toBeCopied; i < count; i++) {
            b[i] = nextB[i - toBeCopied];
        }
    }
    avail -= count;
    trainBack();
    return b;
}

void Buffer::sputn(char* b, int count) {
    if (count <= 0) return;
    if (avail == 0) {
        current = b;
        avail = count;
    } else if (next != nullptr) {
        next->sputn(b, count);
    } else next = new Buffer(b, count);
}

void Buffer::trainBack() {
    if (avail <= 0 && next != nullptr) {
        int nextAvail = next->in_avail();
        if (nextAvail > 0) {
            avail = nextAvail;
            current = next->sgetn(nextAvail);
        }
        delete next;
        next = nullptr;
    }
}