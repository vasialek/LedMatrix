#pragma once

#include "../models/matrixsnapshot.h"

class IEffectRunner
{
public:
    virtual void Move() = 0;
    virtual int SetDelayMs(int delayMs) = 0;
    virtual void Reset() = 0;
    virtual MatrixSnapshot* GetSnapshot() = 0;
    virtual int SwitchNextColor() = 0;
};
