#pragma once

#ifndef ARDUINO
#include "../interfaces/ilogger.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

class ConsoleLogger : public ILogger
{
    std::string GetTime();
    void Log(const char* logLevel, const char* msg);

public:
    void Info(const char* msg);
    void Debug(const char* msg);
};

inline void ConsoleLogger::Info(const char* msg)
{
    Log("INF", msg);
}

inline void ConsoleLogger::Debug(const char* msg)
{
    Log("DBG", msg);
}

inline void ConsoleLogger::Log(const char* logLevel, const char* msg)
{
    std::cout << GetTime() << "[" << logLevel << "] " << msg << std::endl;
}

inline std::string ConsoleLogger::GetTime()
{
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%T ");
    return ss.str();
}

#endif
