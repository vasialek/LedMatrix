#pragma once

#include "baseeffectrunner.h"
#include "acolors.h"

class RandomPoint : public BaseEffectRunner
{
private:
    int _currentColor = ACOLOR_MIN;
public:
    RandomPoint(/* args */);

    void Move();
    void Reset();
    MatrixSnapshot *GetSnapshot();

    ~RandomPoint();
};

RandomPoint::RandomPoint(/* args */)
{
}

void RandomPoint::Move()
{

}

void RandomPoint::Reset()
{

}

MatrixSnapshot *RandomPoint::GetSnapshot()
{

}

// int RandomPoint::SwitchNextColor()
// {

// }


RandomPoint::~RandomPoint()
{
}

