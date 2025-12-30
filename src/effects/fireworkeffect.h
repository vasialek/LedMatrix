#pragma once

#include <cstdint>
#include <cstdio>

#include "baseeffectrunner.h"
#include "../matrixhelper.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/ilogger.h"
#include "../models/acolors.h"

class FireworkEffect : public BaseEffectRunner
{
    MatrixSnapshot _snapshot;
    IDateTimeProvider* _dateTimeProvider;
    MatrixHelper* _matrixHelper;
    ILogger* _logger;
    unsigned long _lastTickAt = 0;
    unsigned long _tickDelay = 2000;
    int _fireworkPhase = 0;
    int _fireworkX, _fireworkY, _fireworkSize = 4;
    void SetPixelSafe(int x, int y, uint8_t color);
    void SetStarburstPixels(int x, int y, int distance, uint8_t color);

public:
    FireworkEffect(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, ILogger* logger, int width, int height)
    {
        _dateTimeProvider = dateTimeProvider;
        _matrixHelper = matrixHelper;
        _logger = logger;

        _snapshot.totalCells = width * height;
        _snapshot.cells = new uint8_t[_snapshot.totalCells];
        Reset();
    }

    void Move() override
    {
        auto now = _dateTimeProvider->millis();
        if (now - _lastTickAt < _tickDelay)
        {
            return;
        }
        _lastTickAt = now;

        char buffer[128];
        sprintf(buffer, "Phase %d", _fireworkPhase);
        _logger->Debug(buffer);
        switch (_fireworkPhase)
        {
        case 0:
            _fireworkX = 5;
            _fireworkY = 5;
            SetStarburstPixels(_fireworkX, _fireworkY, 0, ACOLOR_BLUE);
            break;
        case 1:
            SetStarburstPixels(_fireworkX, _fireworkY, 1, ACOLOR_GREEN);
            break;
        case 2:
            SetStarburstPixels(_fireworkX, _fireworkY, 2, ACOLOR_ORANGE);
            SetStarburstPixels(_fireworkX, _fireworkY, 0, ACOLOR_OFF);
            break;
        case 3:
            SetStarburstPixels(_fireworkX, _fireworkY, 3, ACOLOR_ORANGE);
            SetStarburstPixels(_fireworkX, _fireworkY, 1, ACOLOR_OFF);
            break;
        case 4:
            SetStarburstPixels(_fireworkX, _fireworkY, 2, ACOLOR_OFF);
            break;
        case 5:
            SetStarburstPixels(_fireworkX, _fireworkY, 3, ACOLOR_OFF);
            _isFinished = true;
            break;
        default:
            Reset();
            break;
        }

        _fireworkPhase++;
    }

    void Reset() override
    {
        _isFinished = false;
        _fireworkPhase = 0;
        FillMatrix(ACOLOR_OFF);
    }

    MatrixSnapshot* GetSnapshot() override
    {
        return &_snapshot;
    }

    virtual ~FireworkEffect()
    {
        if (_snapshot.cells != nullptr)
        {
            delete[] _snapshot.cells;
        }
    }
};

void FireworkEffect::SetPixelSafe(int x, int y, uint8_t color)
{
    auto index = _matrixHelper->GetMatrixIndex(x, y);
    if (index < 0 || index >= _snapshot.totalCells)
    {
        return;
    }
    _snapshot.cells[index] = color;
}

inline void FireworkEffect::SetStarburstPixels(int x, int y, int distance, uint8_t color)
{
    if (distance == 0)
    {
        SetPixelSafe(x, y, color);
        return;
    }

    SetPixelSafe(x, y - distance, color);
    SetPixelSafe(x, y + distance, color);
    SetPixelSafe(x - distance, y, color);
    SetPixelSafe(x + distance, y, color);

    SetPixelSafe(x - distance, y - distance, color);
    SetPixelSafe(x + distance, y - distance, color);
    SetPixelSafe(x - distance, y + distance, color);
    SetPixelSafe(x + distance, y + distance, color);
}
