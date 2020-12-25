#pragma once

#include <sstream>
#include "../net/MessageIdentifier.h"
#include "MessageFilter.h"

class NewPlayerMessageFilter : public MessageFilter {
    public:
        bool shouldIgnore(char messageType) { return messageType != 0; };
};