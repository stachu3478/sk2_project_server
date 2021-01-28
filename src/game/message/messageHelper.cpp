#include "messageHelper.h"

void insertInteger(char* str, int v) {
    str[0] = (v & 0xff000000) >> 24;
    str[1] = (v & 0x00ff0000) >> 16;
    str[2] = (v & 0x0000ff00) >> 8;
    str[3] = (v & 0x000000ff) >> 0;

    /*
        FFFF
        FF
        FFFF
        FF
        FF
    */
}

int readInteger(Buffer* buff) {
    int val = 0;
    val |= (unsigned char)buff->sbumpc() << 24;
    val |= (unsigned char)buff->sbumpc() << 16;
    val |= (unsigned char)buff->sbumpc() << 8;
    val |= (unsigned char)buff->sbumpc() << 0;
    return val;
}