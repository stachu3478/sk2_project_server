#include <string.h>
#include "../../net/MessageOut.h"

class LobbyJoinedMessage : public MessageOut {
    public:
        LobbyJoinedMessage(int minPlayersToStart, int ownerId, int maxPlayersCount) { this->minPlayersToStart = minPlayersToStart; this->ownerId = ownerId; this->maxPlayersCount = maxPlayersCount; };
        virtual ~LobbyJoinedMessage();

        char* serialize();
        int length() { return 4; };
    private:
        int minPlayersToStart;
        int ownerId;
        int maxPlayersCount;
};