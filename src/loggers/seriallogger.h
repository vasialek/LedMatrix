#pragma once

#include "ilogger.h"
#include "datetimeprovider.h"
#include <iostream>
#ifndef ARDUINO
    #include <chrono>
    #include <ctime>
    #include <sstream>
    #include <iomanip>
#endif

class SerialLogger : public ILogger
{
private:
    IDateTimeProvider *_dateTimeProvider = nullptr;
    char _timeBuffer[10];
    char *GetTime();
    void Log(const char *logLevel, const char *msg);
public:
    SerialLogger(IDateTimeProvider *dateTimeProvider);

    void Info(const char *msg);
    void Debug(const char *msg);    
};

SerialLogger::SerialLogger(IDateTimeProvider *dateTimeProvider) {
    _dateTimeProvider = dateTimeProvider;
}

void SerialLogger::Log(const char *logLevel, const char *msg) {
    // temporary, then use Serial.println()
    std::cout << GetTime() << " [" << logLevel << "] " << msg << std::endl;
}

void SerialLogger::Info(const char *msg) {
    Log("INF", msg);
}

void SerialLogger::Debug(const char *msg) {
    Log("DBG", msg);
}

char *SerialLogger::GetTime() {
    auto millis = _dateTimeProvider->millis();

    int seconds = millis / 1000;
    int hours = seconds / 3600;
    seconds -= hours * 3600;
    hours = hours % 24;
    int minutes = seconds / 60;
    seconds -= minutes * 60;

    snprintf(_timeBuffer, 9, "%02d:%02d:%02d", hours, minutes, seconds);
    return _timeBuffer;
}
