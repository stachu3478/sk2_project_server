#include "Logger.h"

void Logger::log(std::string str) {
    auto currTime = std::time(nullptr);
    char* textDate = std::ctime(&currTime);
    textDate[std::strlen(textDate) - 1] = ' ';
    file << "[" << textDate << "] " << str << "\n";
}