#pragma once

#include "ieffectrunner.h"
#include "matrixsnapshot.h"
#include "matrixhelper.h"

class BaseEffectRunner : public IEffectRunner
{
protected:
    int _width = 10, _height = 10;
    int _delayMs = 1;
    unsigned long _lastMoveAt = 0;
    int _currentColor = ACOLOR_MIN;

    MatrixSnapshot _snapshot;

    int GetNextColor();
public:
    int SetDelayMs(int delayMs);
    int SwitchNextColor();
};

int BaseEffectRunner::SetDelayMs(int delayMs)
{
    _delayMs = delayMs;
    return _delayMs;
}

inline int BaseEffectRunner::GetNextColor()
{
    auto color = _currentColor + 1;
    if (color > ACOLOR_MAX)
    {
        color = ACOLOR_MIN;
    }

    return color;
}

int BaseEffectRunner::SwitchNextColor()
{
    _currentColor = GetNextColor();
    return _currentColor;
}
