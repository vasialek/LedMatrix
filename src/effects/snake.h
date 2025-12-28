#pragma once

#include "../models/acolors.h"
#include "../datetimeprovider.h"
#include "../matrixhelper.h"
#include "../providers/randomprovider.h"
#include "../effects/baseeffectrunner.h"

const int MaxLength = 25;

class Snake : public BaseEffectRunner
{
private:
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
    int SwitchNextColor() override;
    void DebugSnake();
    void DebugPoint(int x, int y);

public:
    Snake(IDateTimeProvider* dateTimeProvider,
          IRandomProvider* randomProvider,
          MatrixHelper* matrixHelper,
          int x, int y,
          int dx, int dy);

    void Move();
    void Reset();
    MatrixSnapshot* GetSnapshot();

    ~Snake();
};

Snake::Snake(IDateTimeProvider* dateTimeProvider,
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

    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];

    Reset();
}

void Snake::Move()
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
        y += _dy;
        _dx = -_dx;
    }
    else if (x >= _width)
    {
        x = _width - 1;
        y += _dy;
        _dx = -_dx;
    }
    if (y >= _height)
    {
        y = _height - 1;
        _dy = -_dy;
        _dx = -_dx;
    }
    else if (y < 0)
    {
        y = 0;
        _dy = -_dy;
        _currentColor = SwitchNextColor();
        for (auto i = 1; i < _length; i++)
        {
            auto index = _matrixHelper->GetMatrixIndex(_positionX[i], _positionY[i]);
            _snapshot.cells[index] = ACOLOR_OFF;
        }

        _length = 1;
        _isFinished = true;
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

    if (debug)
    {
        DebugSnake();
    }
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
    _snapshot.cells[index] = ACOLOR_RED;

    return &_snapshot;
}

inline bool Snake::SnakeHitTarget()
{
    return _positionX[0] == _targetX && _positionY[0] == _targetY;
}

inline void Snake::SetNewTarget(int y)
{
    auto targetX = _randomProvider->Random(10);
    auto targetY = y + _dy;
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

inline int Snake::SwitchNextColor()
{
    _currentColor = _currentColor == ACOLOR_BLUE ? ACOLOR_GREEN : ACOLOR_BLUE;
    // Serial.println(_currentColor);
    return _currentColor;
}

inline void Snake::DebugSnake()
{
    // Serial.print("Snake length is ");
    // Serial.print(_length);
    // Serial.print(": [");
    // for (auto i = 0; i < _length; i++)
    // {
    // DebugPoint(_positionX[i], _positionY[i]);
    // }
    // Serial.println("]");
}

inline void Snake::DebugPoint(int x, int y)
{
    // Serial.print("(");
    // Serial.print(x);
    // Serial.print(", ");
    // Serial.print(y);
    // Serial.print(") ");
}

Snake::~Snake()
{
    if (_snapshot.cells != nullptr)
    {
        delete []_snapshot.cells;
    }
}
