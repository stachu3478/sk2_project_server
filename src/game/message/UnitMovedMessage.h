#include <string.h>
#include <unordered_map>
#include "../Unit.h"
#include "../../net/MessageOut.h"
#include "messageHelper.h"

class UnitMovedMessage : public MessageOut {
    public:
        UnitMovedMessage(Unit* unit) { this->toX = unit->getX(); this->toY = unit->getY(); this->unitId = unit->getId(); };
        virtual ~UnitMovedMessage();

        char* serialize();
        int length() { return 13; };
    private:
        int toX;
        int toY;
        int unitId;
};