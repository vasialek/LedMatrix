#pragma once

#include "../models/acolors.h"
#include "../interfaces/ieffectrunner.h"
#include "../models/matrixsnapshot.h"

class BaseEffectRunner : public IEffectRunner
{
protected:
    unsigned int _width = 10, _height = 10;
    unsigned int _delayMs = 1;
    unsigned long _lastMoveAt = 0;
    int _currentColor = ACOLOR_MIN;
    bool _isFinished = true;

    MatrixSnapshot _snapshot;

    int GetNextColor();
    void FillMatrix(int color = ACOLOR_OFF);

public:
    bool IsFinished();
    void Restart();
    int SetDelayMs(int delayMs);
    int SwitchNextColor();
};

inline bool BaseEffectRunner::IsFinished()
{
    return _isFinished;
}

inline void BaseEffectRunner::Restart()
{
    _isFinished = false;
}

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

void BaseEffectRunner::FillMatrix(int color)
{
    if (_snapshot.cells == nullptr)
    {
        return;
    }

    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = color;
    }
}
