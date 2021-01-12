#include "GameMessageIdentifier.h"

GameMessageIdentifier::~GameMessageIdentifier() {}

Message* GameMessageIdentifier::createMessage(std::stringbuf* buffer) {
    printf("Creating messages\n");
    if (buffer->in_avail() == 0) return nullptr;
    printf("Bytes available\n");
    char messageType = buffer->sbumpc();
    printf("Detecting message type\n");
    GameMessage* m = nullptr;
    if (messageType == 0) m = new PlayMessage();
    // else if blablabla
    // ... more message type verifies
    else {
        player->kick("Internal server error");
        return nullptr;
    };
    printf("Message somehow read\n");
    m->setPlayer(player);
    if (filter->shouldIgnore(messageType)) m->ignore();
    return m;
}