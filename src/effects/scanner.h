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
    unsigned int _turns = 0;

    IDateTimeProvider* _dateTimeProvider = nullptr;
    MatrixSnapshot _snapshot;
    MatrixHelper* _matrixHelper = nullptr;

public:
    Scanner(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, int width, int height);

    void Move() override;
    void Reset() override;
    MatrixSnapshot* GetSnapshot() override;

    ~Scanner();
};

Scanner::Scanner(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, int width, int height)
{
    _dateTimeProvider = dateTimeProvider;
    _matrixHelper = matrixHelper;
    _width = width;
    _height = height;

    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];

    _delayMs = 170;
    Reset();
}

void Scanner::Move()
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

            _turns++;
            if (_turns >= ACOLOR_MAX * _width * 10)
            {
                _isFinished = true;
                _turns = 0;
            }
        }
        if (_positions[x] + _dYs[x] < 0)
        {
            _dYs[x] = -_dYs[x];
        }

        _positions[x] += _dYs[x];
    }
}

void Scanner::Reset()
{
    _lastMoveAt = 0;
    _currentColor = ACOLOR_MIN;
    _turns = 0;
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

MatrixSnapshot* Scanner::GetSnapshot()
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

Scanner::~Scanner()
{
    if (_snapshot.cells != nullptr)
    {
        delete []_snapshot.cells;
    }
}
