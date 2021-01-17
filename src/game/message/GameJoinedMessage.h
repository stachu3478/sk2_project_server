#include <string.h>
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class GameJoinedMessage : public MessageOut {
    public:
        GameJoinedMessage(int mapWidth, int mapHeight) { this->mapWidth = mapWidth; this->mapHeight = mapHeight; };
        virtual ~GameJoinedMessage();

        char* serialize();
        int length() { return 13; };
    private:
        int mapWidth;
        int mapHeight;
};