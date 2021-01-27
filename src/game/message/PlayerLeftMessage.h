#include <string.h>
#include "../../net/MessageOut.h"

class PlayerLeftMessage : public MessageOut {
    public:
        PlayerLeftMessage(char ownerId) { this->ownerId = ownerId; };
        virtual ~PlayerLeftMessage() {};

        char* serialize() { return new char[2]{ 10, ownerId }; };
        int length() { return 2; };
    private:
        char ownerId;
};