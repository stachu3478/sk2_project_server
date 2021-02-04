#include "Player.h"

using namespace std;

Player::Player(ClientPtr c) {
    client = c;
    client->setMessageIdentifier(&messageIdentifier);
}

Player::~Player() {}

void Player::kick(const char* reason) {
    if (isOffline()) return;
    KickMessage m(reason);
    emit(&m);
    flush();
    client->disconnect();
}

void Player::addUnit(UnitPtr unit) {
    this->units.insert(pair<int, UnitPtr>(unit->getId(), unit));
    if (!isOffline()) {
        ((GameMessageIdentifier*)client->getMessageIdentifier())->setUnitBatchSize(units.size());
    }
}
