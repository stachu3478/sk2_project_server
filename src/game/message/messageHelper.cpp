#include "messageHelper.h"

void insertInteger(std::string* str, int v) {
    char squashedInt[4];
    squashedInt[0] = (v & 0xf000) >> 24;
    squashedInt[1] = (v & 0x0f00) >> 16;
    squashedInt[2] = (v & 0x00f0) >> 8;
    squashedInt[3] = (v & 0x000f) >> 0;
    str->append(squashedInt, 4);
}