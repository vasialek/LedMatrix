#pragma once

#include "matrixhelper.h"

class BitMatrixParser
{
private:
    MatrixHelper *_matrixHelper = nullptr;

public:
    BitMatrixParser(MatrixHelper *matrixHelper);
    // int* Parse(char)
    ~BitMatrixParser();
};

BitMatrixParser::BitMatrixParser(/* args */)
{
}

BitMatrixParser::~BitMatrixParser()
{
}
