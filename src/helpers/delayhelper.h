#pragma once

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <unistd.h>
#endif

class DelayHelper
{
public:
    static void Delay(int ms)
    {
#ifdef ARDUINO
        delay(ms);
#else
        usleep(ms * 1000);
#endif
    }
};
