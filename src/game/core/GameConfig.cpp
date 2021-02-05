#include "GameConfig.h"

using namespace std;

const char* FILENAME = "config.txt";
GameConfig::GameConfig(Logger* logger) {
    if (access(FILENAME, F_OK) == -1) {
        // save
        ofstream file(FILENAME);
        if (!file.is_open()) {
            logger->log("Warning: Failed to generate configuration file from defaults.");
            return;
        }
        file << "> General:" << endl;
        file << "Server port:" << endl;
        file << port << endl;
        file << "Max players count per game:" << endl;
        file << maxPlayersCountPerGame << endl;
        file << "Min players count to start:" << endl;
        file << minPlayersCountToStart << endl;
        file << "Map width:" << endl;
        file << mapWidth << endl;
        file << "Map height:" << endl;
        file << mapHeight << endl;
        file << "Countdown in seconds:" << endl;
        file << countdownSeconds << endl;
        file << "Tick time in miliseconds:" << endl;
        file << tickTime << endl;
        file << "> Units:" << endl;
        file << "Initial count:" << endl;
        file << units.initialCount << endl;
        file << "Move tick cooldown:" << endl;
        file << units.moveTickCooldown << endl;
        file << "Attack tick cooldown:" << endl;
        file << units.attackTickColldown << endl;
        file << "Attack damage:" << endl;
        file << units.attackDamage << endl;
        file << "Max hitpoints:" << endl;
        file << units.hitpoints << endl;
        file << "Max attack distance:" << endl;
        file << units.maxAttackDistance << endl;
        file.close();
    } else {
        // load
        ifstream file(FILENAME);
        if (!file.is_open()) {
            logger->log("Warning: Failed to load configuration, using defaults.");
            return;
        }
        string keyLine;
        while (getline(file, keyLine)) {
            if (keyLine == "Server port:") file >> port;
            else if (keyLine == "Max players count per game:") file >> maxPlayersCountPerGame;
            else if (keyLine == "Min players count to start:") file >> minPlayersCountToStart;
            else if (keyLine == "Map width:") file >> mapWidth;
            else if (keyLine == "Map height:") file >> mapHeight;
            else if (keyLine == "Countdown in seconds:") file >> countdownSeconds;
            else if (keyLine == "Tick time in miliseconds:") file >> tickTime;
            else if (keyLine == "Initial count:") file >> units.initialCount;
            else if (keyLine == "Move tick cooldown:") file >> units.moveTickCooldown;
            else if (keyLine == "Attack tick cooldown:") file >> units.attackTickColldown;
            else if (keyLine == "Attack damage:") file >> units.attackDamage;
            else if (keyLine == "Max hitpoints:") file >> units.hitpoints;
            else if (keyLine == "Max attack distance:") file >> units.maxAttackDistance;
            else if (!keyLine.starts_with("> ") && !keyLine.empty()) logger->log(string("Warning: Unknown configuration property: ") + keyLine);
        }
        file.close();
    }
}