#pragma once

#include "baseeffectrunner.h"

class MazeGenerator : public BaseEffectRunner {

public:
    void Move();
    void Reset();
    MatrixSnapshot *GetSnapshot();
};

void MazeGenerator::Move() {

}

void MazeGenerator::Reset() {

}

MatrixSnapshot *MazeGenerator::GetSnapshot() {
    return nullptr;
}

