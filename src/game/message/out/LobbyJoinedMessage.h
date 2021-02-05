#include <string.h>
#include "SimpleMessageOut.h"
#include "../../core/GameConfig.h"
#include "../messageHelper.h"

class LobbyJoinedMessage : public SimpleMessageOut {
    public:
        LobbyJoinedMessage(GameConfig* config, int ownerId, int countdownSeconds) { this->config = config; this->ownerId = ownerId; this->countdownSeconds = countdownSeconds; };
        virtual ~LobbyJoinedMessage();

        char* serialize();
        int length() { return 13; };
        char getType() { return 0; };
    private:
        GameConfig* config;
        int ownerId;
        int countdownSeconds;
};