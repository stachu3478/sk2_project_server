#include <string.h>
#include "../../net/MessageOut.h"

class LobbyJoinedMessage : public MessageOut {
    public:
        LobbyJoinedMessage(int minPlayersToStart, int ownerId) { this->minPlayersToStart = minPlayersToStart; this->ownerId = ownerId; };
        virtual ~LobbyJoinedMessage();

        std::string serialize();
    private:
        int minPlayersToStart;
        int ownerId;
};