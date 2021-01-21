#include <string.h>
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class GameJoinedMessage : public MessageOut {
    public:
        GameJoinedMessage() {  };
        virtual ~GameJoinedMessage();

        char* serialize();
        int length() { return 5; };
};