#include "PlayerSpawner.h"

PlayerSpawner::PlayerSpawner(Map* map, UnitFactory* factory, GameConfig* gameConfig) {
    this->map = map;
    this->initialUnitCount = gameConfig->units.initialCount;
    this->maxClock = gameConfig->maxPlayersCountPerGame;
    this->unitHitpoints = gameConfig->units.hitpoints;
    this->unitAttackDamage = gameConfig->units.attackDamage;
    this->factory = factory;
}

PlayerSpawner::~PlayerSpawner() {}

void PlayerSpawner::spawnPlayer(Player* player) {
    //Spawn units
    double spawnDirection = 2 * M_PI * spawnDirectionClock++ / (double)maxClock;
    int spawnX = map->getWidth() / 2 + sin(spawnDirection) * (map->getWidth() / 2 - 1) - 1;
    int spawnY = map->getHeight() / 2 + cos(spawnDirection) * (map->getHeight() / 2 - 1) - 1;
    int spawnRange = 2;
    int unitsToSpawn = initialUnitCount;
    while (unitsToSpawn > 0) {
        for (int i = 1; i < spawnRange * spawnRange; i++) {
            Point* potencialPosition = new Point(spawnX + rand() % spawnRange - spawnRange / 2, spawnY + rand() % spawnRange - spawnRange / 2);
            if (!map->isBlank(potencialPosition)) continue;
            spawnUnit(player, potencialPosition);
            if (--unitsToSpawn <= 0) break;
        }
        spawnRange++;
    }
}

void PlayerSpawner::spawnUnit(Player* player, Point* pos) {
    Unit* unit = factory->create(player->getOwnerId(), unitHitpoints, unitAttackDamage);
    map->setUnit(unit, pos);
    player->addUnit(unit);
}