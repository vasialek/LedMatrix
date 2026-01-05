#pragma once

#include "../models/acolors.h"
#include "../providers/datetimeprovider.h"
#include "../helpers/matrixhelper.h"
#include "../providers/randomprovider.h"
#include "../effects/baseeffectrunner.h"
#include "../helpers/delayhelper.h"

const int MaxLength = 25;

class Snake : public BaseEffectRunner
{
    int _length = 1;
    int _positionX[MaxLength];
    int _positionY[MaxLength];
    int _dx = 1, _dy = 1;
    int _targetX = 0, _targetY = 0;
    IDateTimeProvider* _dateTimeProvider = nullptr;
    IRandomProvider* _randomProvider = nullptr;
    MatrixHelper* _matrixHelper = nullptr;

    bool SnakeHitTarget();
    void SetNewTarget(int y);

public:
    Snake(IDateTimeProvider* dateTimeProvider,
          IRandomProvider* randomProvider,
          MatrixHelper* matrixHelper,
          int x, int y,
          int dx, int dy);

    void Move();
    void Reset();
    MatrixSnapshot* GetSnapshot();
};

inline Snake::Snake(IDateTimeProvider* dateTimeProvider,
                    IRandomProvider* randomProvider,
                    MatrixHelper* matrixHelper,
                    int x, int y,
                    int dx, int dy)
{
    _dateTimeProvider = dateTimeProvider;
    _randomProvider = randomProvider;
    _matrixHelper = matrixHelper;
    _positionX[0] = x;
    _positionY[0] = y;
    _dx = dx;
    _dy = dy;

    _delayMs = 200;
    ResetMatrixSnapshot();
    Reset();
}

inline void Snake::Move()
{
    _isFinished = false;
    bool debug = false;
    auto now = _dateTimeProvider->millis();
    if (now - _lastMoveAt < _delayMs)
    {
        return;
    }
    _lastMoveAt = now;

    auto x = _positionX[0] + _dx;
    auto y = _positionY[0];
    if (x < 0)
    {
        x = 0;
        if (y < 1 && _dy < 0)
        {
            SwitchNextColor();
        }
        y += _dy;
        _dx = -_dx;
    }
    else if (x >= _width)
    {
        if (y < 1 && _dy > 0)
        {
            SwitchNextColor();
        }
        x = _width - 1;
        y += _dy;
        _dx = -_dx;
    }
    if (y >= _height)
    {
        // y = _height - 1;
        _dy = -_dy;
        _dx = -_dx;
    }
    else if (y < 0)
    {
        DelayHelper::Delay(20000);
        // y = 0;
        _dy = -_dy;
        _dx = -_dx;
        _currentColor = SwitchNextColor();
        for (auto i = 1; i < _length; i++)
        {
            auto index = _matrixHelper->GetMatrixIndex(_positionX[i], _positionY[i]);
            _snapshot.cells[index] = ACOLOR_OFF;
        }

        _length = 1;
        DelayHelper::Delay(10000);
        // _isFinished = true;
        // return;
    }

    auto index = _matrixHelper->GetMatrixIndex(_positionX[_length - 1], _positionY[_length - 1]);
    // Serial.print("Deleting point at: ");
    // DebugPoint(_positionX[_length-1], _positionY[_length-1]);
    // Serial.println();
    _snapshot.cells[index] = ACOLOR_OFF;

    if (SnakeHitTarget())
    {
        _length++;
        if (_length >= MaxLength)
        {
            Reset();
            _isFinished = true;
            return;
        }
        SetNewTarget(y);
        // debug = true;
    }

    for (auto i = _length - 1; i > 0; i--)
    {
        _positionX[i] = _positionX[i - 1];
        _positionY[i] = _positionY[i - 1];
    }

    _positionX[0] = x;
    _positionY[0] = y;
}

inline void Snake::Reset()
{
    _length = 1;
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = 0;
    }

    SetNewTarget(_positionY[0]);
    SwitchNextColor();
}

inline MatrixSnapshot* Snake::GetSnapshot()
{
    for (auto i = 0; i < _length; i++)
    {
        auto index = _matrixHelper->GetMatrixIndex(_positionX[i], _positionY[i]);
        _snapshot.cells[index] = _currentColor;
    }
    auto index = _matrixHelper->GetMatrixIndex(_targetX, _targetY);
    _snapshot.cells[index] = _currentColor;

    return &_snapshot;
}

inline bool Snake::SnakeHitTarget()
{
    return _positionX[0] == _targetX && _positionY[0] == _targetY;
}

inline void Snake::SetNewTarget(int y)
{
    unsigned char targetX = _randomProvider->Random(10);
    unsigned char targetY = y + _dy;
    if (targetY < 0)
    {
        targetY = _length > 6 ? 2 : 1;
    }
    else if (targetY > _height - 1)
    {
        targetY = _height - 2;
    }
    _targetX = targetX;
    _targetY = targetY;
}
