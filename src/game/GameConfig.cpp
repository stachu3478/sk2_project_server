#include "GameConfig.h"

const char* FILENAME = "config.txt";
GameConfig::GameConfig() {
    if (access(FILENAME, F_OK) == -1) {
        // save
        std::ofstream file(FILENAME);
        file << "> General:" << std::endl;
        file << "Server port:" << std::endl;
        file << port << std::endl;
        file << "Max players count per game:" << std::endl;
        file << maxPlayersCountPerGame << std::endl;
        file << "Min players count to start:" << std::endl;
        file << minPlayersCountToStart << std::endl;
        file << "Map width:" << std::endl;
        file << mapWidth << std::endl;
        file << "Map height:" << std::endl;
        file << mapHeight << std::endl;
        file << "Countdown in seconds:" << std::endl;
        file << countdownSeconds << std::endl;
        file << "Tick time in miliseconds:" << std::endl;
        file << tickTime << std::endl;
        file << "> Units:" << std::endl;
        file << "Initial count:" << std::endl;
        file << units.initialCount << std::endl;
        file << "Move tick cooldown:" << std::endl;
        file << units.moveTickCooldown << std::endl;
        file << "Attack tick cooldown:" << std::endl;
        file << units.attackTickColldown << std::endl;
        file << "Attack damage:" << std::endl;
        file << units.attackDamage << std::endl;
        file << "Max hitpoints:" << std::endl;
        file << units.hitpoints << std::endl;
        file << "Max attack distance:" << std::endl;
        file << units.maxAttackDistance << std::endl;
        file.close();
    } else {
        // load
        std::ifstream file(FILENAME);
        std::string keyLine;
        std::string valueLine;
        while (std::getline(file, keyLine)) {
            if (!std::getline(file, valueLine)) continue;
            if (valueLine == "Server port:") file >> port;
            if (valueLine == "Max players count per game:") file >> maxPlayersCountPerGame;
            if (valueLine == "Min players count to start:") file >> minPlayersCountToStart;
            if (valueLine == "Map width:") file >> mapWidth;
            if (valueLine == "Map height:") file >> mapHeight;
            if (valueLine == "Countdown in seconds:") file >> countdownSeconds;
            if (valueLine == "Tick time in miliseconds:") file >> tickTime;
            if (valueLine == "Initial count:") file >> units.initialCount;
            if (valueLine == "Move tick cooldown:") file >> units.moveTickCooldown;
            if (valueLine == "Attack tick cooldown:") file >> units.attackTickColldown;
            if (valueLine == "Attack damage:") file >> units.attackDamage;
            if (valueLine == "Max hitpoints:") file >> units.hitpoints;
            if (valueLine == "Max attack distance:") file >> units.maxAttackDistance;
        }
        file.close();
    }
}