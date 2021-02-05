#include "Logger.h"

using namespace std;

void Logger::log(string str) {
    if (!file.is_open()) {
        printf("%s\n", str.c_str());
        return;
    }
    auto currTime = time(nullptr);
    char* textDate = ctime(&currTime);
    textDate[strlen(textDate) - 1] = ' ';
    file << "[" << textDate << "] " << str << "\n";
}