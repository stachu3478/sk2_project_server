#include "Logger.h"

void Logger::log(std::string str) {
    auto currTime = std::time(nullptr);
    char* textDate = std::ctime(&currTime);
    file << textDate << " " << str << "\n";
}