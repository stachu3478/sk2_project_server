#include "Player.h"

Player::Player(Client* c) {
    client = c;
    ill = false;
}

Player::~Player() {
}

void Player::kick(const char* reason) {
    client->emit(new KickMessage(reason));
    client->disconnect();
    ill = true;
}
