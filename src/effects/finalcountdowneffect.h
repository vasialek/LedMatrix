#pragma once
#include <cstdint>

#include "baseeffectrunner.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/ieffectrunner.h"
#include "../helpers/digitpatternhelper.h"

class FinalCountdownEffect : public BaseEffectRunner
{
    MatrixSnapshot _snapshot;
    IDateTimeProvider* _dateTimeProvider;
    MatrixHelper* _matrixHelper = nullptr;
    ILogger* _logger = nullptr;
    int _currentNumber, _width, _height;
    int _currentNumberColor;
    unsigned long _lastNumberChangedAt;

public:
    FinalCountdownEffect(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, ILogger* logger, int width, int height)
    {
        _dateTimeProvider = dateTimeProvider;
        _matrixHelper = matrixHelper;
        _logger = logger;
        _width = width;
        _height = height;

        _snapshot.totalCells = width * height;
        _snapshot.cells = new uint8_t[_snapshot.totalCells];
        Reset();
        DrawDigit(_currentNumber);
    }

    void Move() override
    {
        // char buffer[128];
        if (_isFinished)
        {
            return;
        }

        auto now = _dateTimeProvider->millis();
        if (now - _lastNumberChangedAt < 1000)
        {
            return;
        }

        _lastNumberChangedAt = now;
        if (_currentNumber <= 0)
        {
            _isFinished = true;
            return;
        }

        DrawDigit(_currentNumber);
        _currentNumber--;
    }

    void Reset() override
    {
        _isFinished = false;
        _currentNumber = 5;
        _currentNumberColor = ACOLOR_RED;
        _lastNumberChangedAt = _dateTimeProvider->millis();
    }

    MatrixSnapshot* GetSnapshot() override
    {
        return &_snapshot;
    }

    void DrawDigit(int currentNumber)
    {
        FillMatrix(ACOLOR_OFF);
        const bool* pattern = DigitPatternHelper::GetDigit(currentNumber);
        int digitPatterLength = DigitPatternHelper::GetLength();
        for (int i = 0; i < _snapshot.totalCells; i++)
        {
            if (i < digitPatterLength && pattern[i])
            {
                // snprintf(buffer, sizeof(buffer), "Set [%d] to RED", i);
                // _logger->Debug(buffer);
                _snapshot.cells[i] = ACOLOR_RED;
            }
            else
            {
                _snapshot.cells[i] = ACOLOR_OFF;
            }
        }
    }

    virtual ~FinalCountdownEffect()
    {
        if (_snapshot.cells != nullptr)
        {
            delete[] _snapshot.cells;
        }
    }
};
