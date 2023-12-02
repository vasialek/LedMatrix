#pragma once

#include "ilogger.h"
#include <iostream>
#ifndef ARDUINO
    #include <chrono>
    #include <ctime>
    #include <sstream>
    #include <iomanip>
#endif

class ConsoleLogger : public ILogger
{
private:
    std::string GetTime();
    void Log(const char *logLevel, const char *msg);
public:
    void Info(const char *msg);
    void Debug(const char *msg);    
};

void ConsoleLogger::Info(const char *msg) {
    Log("INF", msg);
}

void ConsoleLogger::Debug(const char *msg) {
    Log("DBG", msg);
}

void ConsoleLogger::Log(const char *logLevel, const char *msg) {
#ifndef ARDUINO
    // GetTime();
    std::cout << GetTime() << "[" << logLevel << "] " << msg << std::endl;
#endif
}

std::string ConsoleLogger::GetTime() {
#ifdef ARDUINO
    std:string emptyTime;
    return emptyTime;
#else
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%T ");
    return ss.str();
#endif
}
