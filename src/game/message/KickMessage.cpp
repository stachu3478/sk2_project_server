#include "KickMessage.h"

KickMessage::~KickMessage() {
    delete reason;
}

char* KickMessage::serialize() {
    char* str = new char[reason->size() + 2];
    str[0] = 9;
    str[1] = reason->size();
    return str;
}