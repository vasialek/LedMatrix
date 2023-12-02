#pragma once

#include "irandomprovider.h"

class RandomProvider : public IRandomProvider
{
public:
    int Random(int max) override;
};

int RandomProvider::Random(int max)
{
    #ifdef ARDUINO
        return random(max);
    #else
        return 0;
    #endif
}
