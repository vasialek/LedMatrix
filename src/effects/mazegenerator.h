#pragma once

#include "baseeffectrunner.h"
#include "mazebuilder.h"

class MazeGenerator : public BaseEffectRunner {

private:
    int _currentLine = 0;
    MazeBuilder *_mazeBuilder = nullptr;
    ILogger *_logger = nullptr;

public:
    MazeGenerator(MazeBuilder *mazeBuilder, ILogger *logger, int width, int height);

    void Move();
    void Reset();
    MatrixSnapshot *GetSnapshot();
};

MazeGenerator::MazeGenerator(MazeBuilder *mazeBuilder, ILogger *logger, int width, int height) {
    _mazeBuilder = mazeBuilder;
    _logger = logger;
    _width = width;
    _height = height;

    _isFinished = false;
    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];
}

void MazeGenerator::Move() {
    char buf[128];
    sprintf(buf, "Building line #%d", _currentLine);
    _logger->Debug(buf);
    if (_currentLine >= _height - 1)
    {
        _isFinished = true;
    }

    _mazeBuilder->BuildLine(_currentLine);
    _currentLine++;
}

void MazeGenerator::Reset() {

}

MatrixSnapshot *MazeGenerator::GetSnapshot() {
    auto cells = _mazeBuilder->GetMaze();
    for (auto i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = cells[i] ? ACOLOR_RED : ACOLOR_OFF;
    }
    
    return &_snapshot;
}

