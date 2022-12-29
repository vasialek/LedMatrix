#pragma once

class IRandomProvider
{
public:
    virtual int Random(int max) = 0;
};
