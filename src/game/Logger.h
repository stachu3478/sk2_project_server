#pragma once

#include <ctime>
#include <cstring>
#include "fstream"

class Logger {
    public:
        Logger(const char* path) { file.open(path, std::ofstream::out | std::ofstream::app); if (!file.is_open()) printf("Warning: Failed to open log file. Using standard output.\n"); };
        virtual ~Logger() { finalize(); };

        void log(std::string str);
        void log(const char* str) { log(std::string(str)); };
        void finalize() { file.close(); }

    private:
        std::ofstream file;
};