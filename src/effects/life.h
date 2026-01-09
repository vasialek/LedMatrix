#pragma once

#include "../models/acolors.h"
#include "../models/matrixsnapshot.h"
#include "../helpers/matrixhelper.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/irandomprovider.h"
#include "baseeffectrunner.h"

class Life : public BaseEffectRunner
{
    int _initialCells = 15;
    char _cells[100];
    int _turn = 0;
    IDateTimeProvider* _dateTimeProvider = nullptr;
    IRandomProvider* _randomProvider = nullptr;
    MatrixSnapshot _snapshot;
    MatrixHelper* _matrixHelper = nullptr;

    int GetFreeCellIndex();
    int CountNeighbours(int x, int y);
    int CalculateLiveCells();

public:
    Life(IDateTimeProvider* dateTimeProvider,
         IRandomProvider* randomProvider,
         MatrixHelper* matrixHelper,
         int width,
         int height,
         int initialCells);

    void Move() override;
    void Reset() override;
    int SwitchNextColor() override;
    MatrixSnapshot* GetSnapshot() override;

    ~Life();
};

Life::Life(IDateTimeProvider* dateTimeProvider,
           IRandomProvider* randomProvider,
           MatrixHelper* matrixHelper,
           int width,
           int height,
           int initialCells)
{
    _dateTimeProvider = dateTimeProvider;
    _randomProvider = randomProvider;
    _matrixHelper = matrixHelper;
    _width = width;
    _height = height;

    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];
    if (initialCells > 5 && initialCells < 99)
    {
        _initialCells = initialCells;
    }

    Reset();
}

inline void Life::Move()
{
    auto now = _dateTimeProvider->millis();
    if (now - _lastMoveAt < _delayMs)
    {
        return;
    }
    _lastMoveAt = now;

    auto updatedCells = 0;
    _isFinished = false;
    for (unsigned char x = 0; x < _width; x++)
    {
        for (unsigned char y = 0; y < _height; y++)
        {
            auto index = _matrixHelper->GetMatrixIndex(x, y);
            auto neighbours = CountNeighbours(x, y);

            switch (neighbours)
            {
            case 3:
                if (_cells[index] == 0)
                {
                    _cells[index] = 3; // new
                    updatedCells++;
                }
            // let survive
            case 2:
                // case 4:
                break;

            default:
                if (_cells[index] == 1)
                {
                    _cells[index] = 2; // dying
                    updatedCells++;
                }
                break;
            }
        }
    }

    if (updatedCells < 2)
    {
        _currentColor = SwitchNextColor();
        Reset();
        _isFinished = true;
        return;
    }

    int liveCells = CalculateLiveCells();

    _turn++;

    if (liveCells < 1)
    {
        _currentColor = SwitchNextColor();
        Reset();
        _isFinished = true;
    }
}

inline void Life::Reset()
{
    _turn = 0;
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _cells[i] = 0;
        _snapshot.cells[i] = 0;
    }

    for (int i = 0; i < _initialCells; i++)
    {
        auto index = GetFreeCellIndex();
        _cells[index] = 1;
    }
}

inline int Life::SwitchNextColor()
{
    _currentColor++;
    if (_currentColor > ACOLOR_MAX)
    {
        _currentColor = ACOLOR_MIN;
    }

    return _currentColor;
}

inline MatrixSnapshot* Life::GetSnapshot()
{
    for (auto index = 0; index < _snapshot.totalCells; index++)
    {
        _snapshot.cells[index] = _cells[index] == 0 ? ACOLOR_OFF : _currentColor;
    }

    return &_snapshot;
}

inline int Life::GetFreeCellIndex()
{
    int index = 0;
    for (auto i = 0; i < 3; i++)
    {
        index = _randomProvider->Random(_snapshot.totalCells);
        if (_cells[index] == 0)
        {
            return index;
        }
    }

    return index;
}

inline int Life::CountNeighbours(int x, int y)
{
    auto neighbours = 0;
    int neighbourX, neighbourY;
    for (auto dx = -1; dx < 2; dx++)
    {
        for (auto dy = -1; dy < 2; dy++)
        {
            if (dx != 0 || dy != 0)
            {
                neighbourX = x + dx;
                neighbourY = y + dy;
                if (neighbourX >= 0 && neighbourY >= 0)
                {
                    auto index = _matrixHelper->GetMatrixIndex(neighbourX, neighbourY);
                    if (_cells[index] == 1)
                    {
                        neighbours++;
                    }
                }
            }
        }
    }

    return neighbours;
}

inline int Life::CalculateLiveCells()
{
    int liveCells = 0;
    for (auto index = 0; index < _snapshot.totalCells; index++)
    {
        if (_cells[index] == 2)
        {
            _cells[index] = 0;
        }
        else if (_cells[index] == 3)
        {
            _cells[index] = 1;
        }
        if (_cells[index] == 1)
        {
            liveCells++;
        }
    }

    return liveCells;
}

inline Life::~Life()
{
    if (_snapshot.cells != nullptr)
    {
        delete []_snapshot.cells;
    }
}
