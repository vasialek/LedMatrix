#pragma once

#include "baseeffectrunner.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/irandomprovider.h"
#include "../models/acolors.h"

class RandomPoint : public BaseEffectRunner
{
    IRandomProvider* _randomProvider;

    int _currentColor = ACOLOR_OFF;
    int _pointAt = -1;
    int _previousPointAt = -1;
    IDateTimeProvider* _dateTimeProvider;

public:
    RandomPoint(IDateTimeProvider* dateTimeProvider, IRandomProvider* randomProvider, int width, int height);

    void Move() override;
    void Reset() override;
    MatrixSnapshot* GetSnapshot() override;
};

inline RandomPoint::RandomPoint(IDateTimeProvider* dateTimeProvider,
                                IRandomProvider* randomProvider,
                                int width,
                                int height)
{
    _randomProvider = randomProvider;
    _dateTimeProvider = dateTimeProvider;

    _delayMs = 1000;

    _width = width;
    _height = height;
    ResetMatrixSnapshot();
}

inline void RandomPoint::Move()
{
    auto now = _dateTimeProvider->millis();
    if (_lastMoveAt > 0 && now - _lastMoveAt < _delayMs)
    {
        return;
    }
    _lastMoveAt = now;

    if (_previousPointAt >= 0)
    {
        _snapshot.cells[_previousPointAt] = ACOLOR_OFF;
    }
    _previousPointAt = _pointAt;
    _pointAt = _randomProvider->Random(_snapshot.totalCells - 1);
    _snapshot.cells[_pointAt] = SwitchNextColor();

    if (_totalMoves++ > 10)
    {
        _isFinished = true;
    }
}

inline void RandomPoint::Reset()
{
    _isFinished = false;
    _totalMoves = 0;
    _previousPointAt = _pointAt = -1;
    FillMatrix(ACOLOR_OFF);
}

inline MatrixSnapshot* RandomPoint::GetSnapshot()
{
    return &_snapshot;
}
