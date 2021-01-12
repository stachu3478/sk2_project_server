#include <string.h>
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class GameJoinedMessage : public MessageOut {
    public:
        GameJoinedMessage(int mapWidth, int mapHeight) { this->mapWidth = mapWidth; this->mapHeight = mapHeight; };
        virtual ~GameJoinedMessage();

        std::string serialize();
    private:
        int mapWidth;
        int mapHeight;
};