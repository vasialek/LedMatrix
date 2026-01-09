#pragma once

#ifndef ARDUINO

#include "colorhelpernative.h"
#include "matrixhelper.h"
#include "colorhelpernative.h"
#include "../interfaces/ilogger.h"
#include "../models/matrixsnapshot.h"

class MatrixHelperNative
{
    MatrixHelper* _matrixHelper;
    ILogger* _logger;
    int _width = 10;
    int _height = 10;
    int _totalLeds = 100;

public:
    MatrixHelperNative(MatrixHelper* matrixHelper, ILogger* logger, int width, int height)
    {
        _matrixHelper = matrixHelper;
        _logger = logger;
        _width = width;
        _height = height;
        _totalLeds = width * height;
    }
    void ShowMatrix(MatrixSnapshot* snapshot);
};

inline void MatrixHelperNative::ShowMatrix(MatrixSnapshot* snapshot)
{
    if (snapshot == nullptr)
    {
        return;
    }
    char buf[_width + 3];
    int index = 0;
    for (int y = 0; y < _height; y++)
    {
        buf[0] = '|';
        for (int x = 0; x < _width; x++)
        {
            index = _matrixHelper->GetMatrixIndex(x, y);
            buf[x + 1] = ColorHelperNative::GetColorSymbol(snapshot->cells[index]);
        }
        buf[_width + 1] = '|';
        buf[_width + 2] = 0;
        _logger->Info(buf);
    }
}

#endif
