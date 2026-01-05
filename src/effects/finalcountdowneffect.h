#pragma once

#include "baseeffectrunner.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/ieffectrunner.h"

class FinalCountdownEffect : public BaseEffectRunner
{
    IDateTimeProvider* _dateTimeProvider = nullptr;
    MatrixHelper* _matrixHelper = nullptr;
    ILogger* _logger = nullptr;
    int _currentNumber;
    int _currentNumberColor;

public:
    FinalCountdownEffect(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, ILogger* logger, int width, int height)
    {
        _dateTimeProvider = dateTimeProvider;
        _matrixHelper = matrixHelper;
        _logger = logger;
        _width = width;
        _height = height;

        _lastMoveAt = 0;
        _delayMs = 2000;
        Reset();
        ResetMatrixSnapshot();
        DrawDigit(_currentNumber);
    }

    void Move() override
    {
        // Serial.println("FinalCountdownEffect Move");
        // char buffer[128];
        if (_isFinished)
        {
            return;
        }

        auto now = _dateTimeProvider->millis();
        if (_lastMoveAt > 0 && now - _lastMoveAt < _delayMs)
        {
            return;
        }

        _lastMoveAt = now;
        if (_currentNumber <= 0)
        {
            _isFinished = true;
            return;
        }

        for (int i = 0; i < _snapshot.totalCells; i++)
        {
            _snapshot.cells[i] = ACOLOR_OFF;
        }
        DrawDigit(_currentNumber);
        _currentNumber--;
    }

    void Reset() override
    {
        _isFinished = false;
        _currentNumber = 5;
        // _currentNumber = 3;
        _currentNumberColor = ACOLOR_RED;
        _lastMoveAt = _dateTimeProvider->millis();
    }

    MatrixSnapshot* GetSnapshot() override
    {
        return &_snapshot;
    }

    void DrawDigit(int currentNumber)
    {
        // FillMatrix(ACOLOR_OFF);
        switch (currentNumber)
        {
        case 1:
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 1)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 2)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 3)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 4)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 5)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 6)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 6)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 7)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 8)] = ACOLOR_RED;
            break;
        case 2:
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 1)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(8, 2)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 3)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 4)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 5)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 6)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 6)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 7)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(8, 8)] = ACOLOR_RED;
            break;

        case 3:
            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 1)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 2)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 3)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 4)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 5)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 6)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 6)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 7)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 8)] = ACOLOR_RED;
            break;
        case 4:
            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 1)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 2)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 3)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 4)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 5)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 6)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 6)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 7)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 8)] = ACOLOR_RED;
            break;

        case 5:
            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 1)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 1)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 2)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 2)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 3)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 3)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 4)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 4)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 5)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(8, 5)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 6)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(8, 6)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 7)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(8, 7)] = ACOLOR_RED;

            _snapshot.cells[_matrixHelper->GetMatrixIndex(2, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(3, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(4, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(5, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(6, 8)] = ACOLOR_RED;
            _snapshot.cells[_matrixHelper->GetMatrixIndex(7, 8)] = ACOLOR_RED;
            break;
        }
    }
};
