#include <string.h>
#include "SimpleMessageOut.h"

class KickMessage : public SimpleMessageOut {
    public:
        KickMessage(const char* reason) { this->reason = new std::string(reason); };
        virtual ~KickMessage();

        char* serialize();
        int length() { return reason->size() + 2; };
        char getType() { return 9; }
    private:
        std::string* reason;
};