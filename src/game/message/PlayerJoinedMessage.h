#include <string.h>
#include "../../net/MessageOut.h"

class PlayerJoinedMessage : public MessageOut {
    public:
        PlayerJoinedMessage(std::string nickname, int ownerId) { this->nickname = nickname; this->ownerId = ownerId; };
        virtual ~PlayerJoinedMessage();

        char* serialize();
        int length() { return 3 + nickname.size(); };
    private:
        std::string nickname;
        int ownerId;
};