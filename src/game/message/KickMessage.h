#include <string.h>
#include "../../net/MessageOut.h"

class KickMessage : public MessageOut {
    public:
        KickMessage(const char* reason) { this->reason = new std::string(reason); };
        virtual ~KickMessage();

        std::string serialize();
    private:
        std::string* reason;
};