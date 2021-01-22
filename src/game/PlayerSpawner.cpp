#include "PlayerSpawner.h"

PlayerSpawner::PlayerSpawner(Map* map, UnitFactory* factory, int initialUnitCount, int maxClock) {
    this->map = map;
    this->initialUnitCount = initialUnitCount;
    this->maxClock = maxClock;
    this->factory = factory;
}

PlayerSpawner::~PlayerSpawner() {}

void PlayerSpawner::spawnPlayer(Player* player) {
    //Spawn units
    double spawnDirection = 2 * M_PI * spawnDirectionClock++ / (double)maxClock;
    int spawnX = sin(spawnDirection) * (map->getWidth() - 1);
    int spawnY = cos(spawnDirection) * (map->getHeight() - 1);
    int spawnRange = 2;
    int unitsToSpawn = initialUnitCount;
    while (unitsToSpawn > 0) {
        for (int i = 1; i < spawnRange * spawnRange; i++) {
            int potencialX = spawnX + rand() % spawnRange;
            int potencialY = spawnY + rand() % spawnRange;
            if (!map->isBlank(potencialX, potencialY)) continue;
            spawnUnit(player, potencialX, potencialY);
            if (--unitsToSpawn <= 0) break;
        }
        spawnRange++;
    }
}

void PlayerSpawner::spawnUnit(Player* player, int xPos, int yPos) {
    Unit* unit = factory->create(player->getOwnerId());
    map->setUnit(unit, xPos, yPos);
    player->addUnit(unit);
}