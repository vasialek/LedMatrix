#pragma once

#ifdef ARDUINO
    #include <Arduino.h>
#else
    #include <cstdio> // Keep for PC/Linux only
#endif
#include "baseeffectrunner.h"
#include "../matrixhelper.h"
#include "../interfaces/idatetimeprovider.h"
#include "../interfaces/ilogger.h"
#include "../interfaces/irandomprovider.h"
#include "../models/acolors.h"

class FireworkEffect : public BaseEffectRunner
{
    MatrixSnapshot _snapshot;
    IDateTimeProvider* _dateTimeProvider;
    MatrixHelper* _matrixHelper;
    IRandomProvider* _randomProvider;
    ILogger* _logger;
    unsigned long _lastTickAt = 0;
    int _fireworkPhase = 0;
    int _fireworkX, _fireworkY, _fireworkSize = 4;
    int _totalFireworks = 0;
    void SetPixelSafe(int x, int y, unsigned char color);
    void SetStarburstPixels(int x, int y, int distance, unsigned char color);

public:
    FireworkEffect(IDateTimeProvider* dateTimeProvider, MatrixHelper* matrixHelper, IRandomProvider* randomProvider, ILogger* logger, int width, int height)
    {
        _dateTimeProvider = dateTimeProvider;
        _matrixHelper = matrixHelper;
        _randomProvider = randomProvider;
        _logger = logger;

        _snapshot.totalCells = width * height;
        _snapshot.cells = new unsigned char[_snapshot.totalCells];
        _delayMs = 500;
        Reset();
    }

    void Move() override
    {
        int dx, dy;
        auto now = _dateTimeProvider->millis();
        if (now - _lastTickAt < _delayMs)
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
            dx = _randomProvider->Random(4) - 2;
            dy = _randomProvider->Random(5) - 1;
            _fireworkX = 5 + dx;
            _fireworkY = 5 + dy;
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

void FireworkEffect::SetPixelSafe(int x, int y, unsigned char color)
{
    auto index = _matrixHelper->GetMatrixIndex(x, y);
    if (index < 0 || index >= _snapshot.totalCells)
    {
        return;
    }
    _snapshot.cells[index] = color;
}

inline void FireworkEffect::SetStarburstPixels(int x, int y, int distance, unsigned char color)
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
