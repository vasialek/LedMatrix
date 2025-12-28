#pragma once

#include "../interfaces/irandomprovider.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdlib>
#include <ctime>
#endif

class RandomProvider : public IRandomProvider
{
public:
    RandomProvider()
    {
#ifdef ARDUINO
        randomSeed(analogRead(0));
#else
        srand(time(nullptr));
#endif
    }

    int Random(int max) override;
};

inline int RandomProvider::Random(int max)
{
    if (max <= 0)
    {
        return 0;
    }
#ifdef ARDUINO
    return random(max);
#else
#ifdef WINDOWS
    return 0;
#else
    return rand() % max;
#endif
#endif
}
