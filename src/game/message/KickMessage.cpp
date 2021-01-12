#include "KickMessage.h"

KickMessage::~KickMessage() {
    delete reason;
}

std::string KickMessage::serialize() {
    std::string msg(*reason);
    msg.push_back(9);
    msg.push_back(msg.size() - 1);
    return msg;
}