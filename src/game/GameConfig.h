#pragma once

struct GameUnitConfig
{
    unsigned int initialCount = 10;
    unsigned int moveTickCooldown = 8;
    unsigned int attackTickColldown = 35;
    unsigned int attackDamage = 5;
    unsigned int hitpoints = 50;
    unsigned int maxAttackDistance = 5;
};

struct GameConfig {
    unsigned int maxPlayersCountPerGame = 4;
    unsigned int minPlayersCountToStart = 2;
    unsigned int mapWidth = 100;
    unsigned int mapHeight = 100;
    unsigned int countdownSeconds = 10;
    unsigned int tickTime = 50; // tick time in miliseconds
    unsigned int countdownTicks() { return countdownSeconds * 1000 / tickTime; };
    GameUnitConfig units;
};