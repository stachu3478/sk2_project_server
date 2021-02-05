#include "KickMessage.h"

char* KickMessage::serialize() {
    char* str = SimpleMessageOut::serialize();
    str[1] = reasonStr.size();
    strcpy(str + 2, reasonStr.c_str());
    return str;
}