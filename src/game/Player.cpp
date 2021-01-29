#include "Player.h"

Player::Player(Client* c) {
    client = c;
}

Player::~Player() {
}

void Player::emit(MessageOut* m) {
    if (client == nullptr) return;
    if (client->getFd() == -1) {
        delete client;
        client = nullptr;
        return;
    }
    client->emit(m);
}

void Player::kick(const char* reason) {
    client->emit(new KickMessage(reason));
    client->disconnect();
}

void Player::addUnit(Unit* unit) {
    this->units.insert(std::pair<int, Unit*>(unit->getId(), unit));
    if (!isOffline()) {
        ((GameMessageIdentifier*)client->getMessageIdentifier())->setUnitBatchSize(units.size());
    }
}
