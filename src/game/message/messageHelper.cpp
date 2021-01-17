#include "messageHelper.h"

void insertInteger(char* str, int v) {
    str[0] = (v & 0xf000) >> 24;
    str[1] = (v & 0x0f00) >> 16;
    str[2] = (v & 0x00f0) >> 8;
    str[3] = (v & 0x000f) >> 0;
}