#pragma once

#include <iostream>
#ifndef ARDUINO
    #include <chrono>
    #include <ctime>
    #include <sstream>
    #include <iomanip>
#endif

class ILogger
{
public:
    virtual void Info(const char *msg) = 0;
    virtual void Debug(const char *msg) = 0;
};
