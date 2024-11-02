#pragma once
#include <iostream>
#include <fstream>

enum LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
    Logger();
    Logger(const std::string& filename);
    ~Logger();
    void log(LogLevel level, const std::string& message);
    void setLogFile(const std::string& filename);

private:
    std::ofstream logFile;
    std::string levelToString(LogLevel level);
};
