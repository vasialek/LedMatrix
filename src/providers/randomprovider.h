#pragma once

#include "irandomprovider.h"

class RandomProvider : public IRandomProvider
{
public:
    RandomProvider() {
        srand(time(nullptr));
    }
    int Random(int max) override;
};

int RandomProvider::Random(int max)
{
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
