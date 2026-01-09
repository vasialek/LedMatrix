#pragma once

#define LOG_BUFFER_SIZE 256

class ILogger
{
public:
    char buffer[LOG_BUFFER_SIZE];
    virtual void Info(const char* msg) = 0;
    virtual void Debug(const char* msg) = 0;
};
