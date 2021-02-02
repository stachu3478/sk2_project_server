#include <string.h>
#include "SimpleMessageOut.h"

class PlayerLeftMessage : public SimpleMessageOut {
    public:
        PlayerLeftMessage(char ownerId) { this->ownerId = ownerId; };
        virtual ~PlayerLeftMessage() {};

        char* serialize() { return new char[2]{ getType(), ownerId }; };
        int length() { return 2; };
        char getType() { return 10; };
    private:
        char ownerId;
};