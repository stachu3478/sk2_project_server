#include <string.h>
#include "../../net/MessageOut.h"
#include "../GameConfig.h"
#include "messageHelper.h"

class LobbyJoinedMessage : public MessageOut {
    public:
        LobbyJoinedMessage(GameConfig config, int ownerId, int countdownSeconds) { this->config = config; this->ownerId = ownerId; this->countdownSeconds = countdownSeconds; };
        virtual ~LobbyJoinedMessage();

        char* serialize();
        int length() { return 13; };
    private:
        GameConfig config;
        int ownerId;
        int countdownSeconds;
};