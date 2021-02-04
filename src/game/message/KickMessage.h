#include <string.h>
#include "SimpleMessageOut.h"

class KickMessage : public SimpleMessageOut {
    public:
        KickMessage(const char* reason) : reasonStr{reason} { };
        virtual ~KickMessage() {};

        char* serialize();
        int length() { return reasonStr.size() + 2; };
        char getType() { return 9; }
    private:
        std::string reasonStr;
};