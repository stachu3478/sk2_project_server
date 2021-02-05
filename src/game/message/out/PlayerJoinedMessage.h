#include <string.h>
#include "SimpleMessageOut.h"

class PlayerJoinedMessage : public SimpleMessageOut {
    public:
        PlayerJoinedMessage(std::string nickname, int ownerId) { this->nickname = nickname; this->ownerId = ownerId; };
        virtual ~PlayerJoinedMessage();

        char* serialize();
        int length() { return 3 + nickname.size(); };
        char getType() { return 2; };
    private:
        std::string nickname;
        int ownerId;
};