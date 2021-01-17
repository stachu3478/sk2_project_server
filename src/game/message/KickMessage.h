#include <string.h>
#include "../../net/MessageOut.h"

class KickMessage : public MessageOut {
    public:
        KickMessage(const char* reason) { this->reason = new std::string(reason); };
        virtual ~KickMessage();

        char* serialize();
        int length() { return reason->size() + 2; };
    private:
        std::string* reason;
};