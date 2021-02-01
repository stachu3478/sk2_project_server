#include "Player.h"

Player::Player(Client* c) {
    client = c;
    client->setMessageIdentifier(&messageIdentifier);
}

Player::~Player() {}

void Player::emit(MessageOut* m) {
    if (client == nullptr) return;
    client->emit(m);
}

void Player::flush() {
    if (client == nullptr) return;
    if (client->getFd() == -1) {
        delete client;
        client = nullptr;
        return;
    }
    client->flush();
}

void Player::kick(const char* reason) {
    client->emit(new KickMessage(reason));
    client->flush();
    client->disconnect();
}

void Player::addUnit(UnitPtr unit) {
    this->units.insert(std::pair<int, UnitPtr>(unit->getId(), unit));
    if (!isOffline()) {
        ((GameMessageIdentifier*)client->getMessageIdentifier())->setUnitBatchSize(units.size());
    }
}
