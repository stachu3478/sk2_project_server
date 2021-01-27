#pragma once

#include <ctime>
#include "fstream"
#include "ios"

class Logger {
    public:
        Logger(const char* path) { file.open(path, std::ofstream::out | std::ofstream::app); };
        virtual ~Logger() { finalize(); };

        void log(std::string str);
        void log(const char* str) { log(std::string(str)); };
        void finalize() { file.close(); }

    private:
        std::ofstream file;
};