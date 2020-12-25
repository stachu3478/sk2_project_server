#pragma once

class MessageFilter {
    public:
        virtual bool shouldIgnore(char messageId) = 0;
};