#include "KickMessage.h"

KickMessage::~KickMessage() {
    delete reason;
}

char* KickMessage::serialize() {
    char* str = SimpleMessageOut::serialize();
    str[1] = reason->size();
    strcpy(str + 2, reason->c_str());
    return str;
}