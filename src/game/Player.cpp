#include "Player.h"

Player::Player(Client* c) {
    client = c;
    if (c == nullptr) printf("warn client is null\n");
    ill = false;
}

Player::~Player() {
}

void Player::kick(const char* reason) {
    client->emit(new KickMessage(reason));
    client->disconnect();
    ill = true;
}
