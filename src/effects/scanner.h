#pragma once

// #include <iostream>
#include "acolors.h"
#include "matrixsnapshot.h"
#include "matrixhelper.h"
#include "idatetimeprovider.h"

class Scanner
{
private:
    int _width = 10, _height = 10;
    int _positions[10];
    int _dYs[10];
    int _currentColor = ACOLOR_MIN;
    unsigned long _delayMs = 300;
    unsigned long _lastMoveAt = 0;
    IDateTimeProvider *_dateTimeProvider = nullptr;
    MatrixSnapshot _snapshot;
    MatrixHelper *_matrixHelper = nullptr;

public:
    Scanner(IDateTimeProvider *dateTimeProvider, MatrixHelper *matrixHelper, int width, int height);

    void Move();

    void Reset();
    int SwitchNextColor();
    void SetDelayMs(int delayMs);
    MatrixSnapshot *GetSnapshot();

    ~Scanner();
};

Scanner::Scanner(IDateTimeProvider *dateTimeProvider, MatrixHelper *matrixHelper, int width, int height)
{
    _dateTimeProvider = dateTimeProvider;
    _matrixHelper = matrixHelper;
    _width = width;
    _height = height;

    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];

    Reset();    
}

void Scanner::SetDelayMs(int delayMs)
{
    _delayMs = delayMs;
}

void Scanner::Move()
{
    auto now = _dateTimeProvider->millis();
    // std::cout << "  now: " << now << ", last move at " << _lastMoveAt << "\n";
    if (now - _lastMoveAt < _delayMs)
    {
        return;
    }
    _lastMoveAt = now;

    for (size_t x = 0; x < _width; x++)
    {
        if (_positions[x] + _dYs[x] >= _height)
        {
            _currentColor = SwitchNextColor();
            _dYs[x] = -_dYs[x];
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
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = 0;
    }

    for (int x = 0; x < _width; x += 2)
    {
        _positions[x] = 0;
        _dYs[x] = 1;
    }
    for (int x = 1; x < _width; x += 2)
    {
        _positions[x] = 9;
        _dYs[x] = -1;
    }
}

int Scanner::SwitchNextColor()
{
    _currentColor++;
    if (_currentColor > ACOLOR_MAX)
    {
        _currentColor = ACOLOR_MIN;
    }

    return _currentColor;
}

MatrixSnapshot *Scanner::GetSnapshot()
{
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = ACOLOR_OFF;
    }

    for (int x = 0; x < _width; x++)
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
