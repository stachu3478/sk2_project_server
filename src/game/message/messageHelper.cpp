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