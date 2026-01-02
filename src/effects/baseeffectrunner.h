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
    unsigned char _currentColor = ACOLOR_OFF;
    bool _isFinished = true;

    MatrixSnapshot _snapshot;

    int GetNextColor();
    void FillMatrix(unsigned char color = ACOLOR_OFF);

public:
    bool IsFinished();
    void Restart();
    int SetDelayMs(int delayMs) override;
    int SwitchNextColor() override;
};

inline bool BaseEffectRunner::IsFinished()
{
    return _isFinished;
}

inline void BaseEffectRunner::Restart()
{
    _isFinished = false;
}

inline int BaseEffectRunner::SetDelayMs(int delayMs)
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

inline int BaseEffectRunner::SwitchNextColor()
{
    _currentColor = GetNextColor();
    return _currentColor;
}

inline void BaseEffectRunner::FillMatrix(unsigned char color)
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
