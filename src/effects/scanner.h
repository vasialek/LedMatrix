#pragma once

#include "../models/acolors.h"
#include "../models/matrixsnapshot.h"
#include "../helpers/matrixhelper.h"
#include "../interfaces/idatetimeprovider.h"
#include "../effects/baseeffectrunner.h"

class Scanner : public BaseEffectRunner
{
    unsigned int _positions[10];
    unsigned int _dYs[10];

    IDateTimeProvider* _dateTimeProvider = nullptr;
    MatrixHelper* _matrixHelper = nullptr;

public:
    Scanner(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, int width, int height);

    void Move() override;
    void Reset() override;
    MatrixSnapshot* GetSnapshot() override;
};

inline Scanner::Scanner(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, int width, int height)
{
    _dateTimeProvider = dateTimeProvider;
    _matrixHelper = matrixHelper;
    _width = width;
    _height = height;

    ResetMatrixSnapshot();

    _delayMs = 170;
    Reset();
}

inline void Scanner::Move()
{
    auto now = _dateTimeProvider->millis();
    if (now - _lastMoveAt < _delayMs)
    {
        return;
    }
    _lastMoveAt = now;

    _isFinished = false;
    for (unsigned char x = 0; x < _width; x++)
    {
        if (_positions[x] + _dYs[x] >= _height)
        {
            _currentColor = SwitchNextColor();
            _dYs[x] = -_dYs[x];

            _totalMoves++;
            if (_totalMoves >= ACOLOR_MAX * _width * 3)
            {
                _isFinished = true;
                _totalMoves = 0;
            }
        }
        if (_positions[x] + _dYs[x] < 0)
        {
            _dYs[x] = -_dYs[x];
        }

        _positions[x] += _dYs[x];
    }
}

inline void Scanner::Reset()
{
    _lastMoveAt = 0;
    _currentColor = ACOLOR_MIN;
    _totalMoves = 0;
    _isFinished = false;
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = 0;
    }

    for (unsigned char x = 0; x < _width; x += 2)
    {
        _positions[x] = 0;
        _dYs[x] = 1;
    }
    for (unsigned char x = 1; x < _width; x += 2)
    {
        _positions[x] = 9;
        _dYs[x] = -1;
    }
}

inline MatrixSnapshot* Scanner::GetSnapshot()
{
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = ACOLOR_OFF;
    }

    for (unsigned int x = 0; x < _width; x++)
    {
        auto index = _matrixHelper->GetMatrixIndex(x, _positions[x]);
        _snapshot.cells[index] = _currentColor;
    }

    return &_snapshot;
}
