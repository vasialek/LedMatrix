#pragma once

#include "baseeffectrunner.h"

class MazeGenerator : public BaseEffectRunner {

private:
    int _moves = 0;
    ILogger *_logger = nullptr;

public:
    MazeGenerator(ILogger *logger, int width, int height);

    void Move();
    void Reset();
    MatrixSnapshot *GetSnapshot();
};

MazeGenerator::MazeGenerator(ILogger *logger, int width, int height) {
    _logger = logger;
    _width = width;
    _height = height;

    _isFinished = false;
    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];
}

void MazeGenerator::Move() {
    _logger->Debug("Moving...");
    if (++_moves > 90)
    {
        _isFinished = true;
    }

    _snapshot.cells[_moves] = ACOLOR_BLUE;
}

void MazeGenerator::Reset() {

}

MatrixSnapshot *MazeGenerator::GetSnapshot() {
    return &_snapshot;
}

