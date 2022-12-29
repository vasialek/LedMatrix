#pragma once

#include "effectrunner.h"
#include "matrixsnapshot.h"
#include "matrixhelper.h"

class BaseEffectRunner : public IEffectRunner
{
protected:
    int _delayMs = 1;
    int _currentColor = ACOLOR_MIN;

    MatrixSnapshot _snapshot;
public:
    int SetDelayMs(int delayMs);
    int SwitchNextColor();
};

int BaseEffectRunner::SetDelayMs(int delayMs)
{
    _delayMs = delayMs;
    return _delayMs;
}

int BaseEffectRunner::SwitchNextColor()
{
    _currentColor++;
    if (_currentColor > ACOLOR_MAX)
    {
        _currentColor = ACOLOR_MIN;
    }

    return _currentColor;
}
