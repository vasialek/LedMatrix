#pragma once

#include "matrixsnapshot.h"
#include "matrixhelper.h"

// #include <iostream>

class BallMover
{
private:
    int _width = 10, _height = 10;
    int _ballX = 0, _ballY = 0;
    int _ballDx = 1, _ballDy = 1;
    MatrixSnapshot _snapshot;
    MatrixHelper *_matrixHelper = nullptr;
public:
    BallMover(MatrixHelper *matrixHelper, int width, int height);
    void SetBall(int ballX, int ballY);
    void Move();
    int ReverseDx();
    int ReverseDy();
    MatrixSnapshot *GetSnapshot();

    ~BallMover();
};

BallMover::BallMover(MatrixHelper *matrixHelper, int width, int height)
{
    _matrixHelper = matrixHelper;
    _width = width;
    _height = height;
    SetBall(0, 0);
    _snapshot.totalCells = _width * _height;
    _snapshot.cells = new unsigned char[_width * _height];
    for (int i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = 0;
    }
}

void BallMover::SetBall(int ballX, int ballY)
{
    _ballX = ballX;
    _ballY = ballY;
}

void BallMover::Move()
{
    // std::cout << "_ball at: " << _ballX << ", " << _ballY << "\n";
    // std::cout << "  direction: " << _ballDx << ", " << _ballDy << "\n";
    if (_ballX + _ballDx >= _width || _ballX + _ballDx < 0)
    {
        ReverseDx();
    }
    
    if (_ballY + _ballDy >= _height || _ballY + _ballDy < 0)
    {
        ReverseDy();
    }
    
    _ballX += _ballDx;
    _ballY += _ballDy;
}

int BallMover::ReverseDx()
{
    _ballDx = -_ballDx;
    return _ballDx;
}

int BallMover::ReverseDy()
{
    _ballDy = -_ballDy;
    return _ballDy;
}

MatrixSnapshot *BallMover::GetSnapshot()
{
    auto index = _matrixHelper->GetMatrixIndex(_ballX, _ballY);
    for (size_t i = 0; i < _snapshot.totalCells; i++)
    {
        _snapshot.cells[i] = 0;
    }
    
    _snapshot.cells[index] = 1;
    return &_snapshot;
}

BallMover::~BallMover()
{
    if (_snapshot.cells != nullptr)
    {
        delete []_snapshot.cells;
    }
}
