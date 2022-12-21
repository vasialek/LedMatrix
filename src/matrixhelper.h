#pragma once

// #include <iostream>

class MatrixHelper
{
private:
    int _width = 10;
    int _height = 10;
    int _totalLeds = 100;
public:
    MatrixHelper();
    bool IsReversedRow(int row);
    int GetMatrixIndex(int x, int y);
};

MatrixHelper::MatrixHelper()
{
    _totalLeds = _width * _height;
}

int MatrixHelper::GetMatrixIndex(int x, int y)
{
    // std::cout << "--------------------------------------\n";
    // std::cout << "x: " << x << ", y: " << y << "\n";
    int offset = x * _height;
    // std::cout << "offset: " << offset << "\n";

    if (IsReversedRow(x))
    {
        return _totalLeds - ((x + 1) * _height) + (_height - y) - 1;
        // return _totalLeds - offset - _height + y - 1;
    }


    return _totalLeds - offset - (_height - y);
}

bool MatrixHelper::IsReversedRow(int row)
{
    return (_width - row) %2 == 0;
}
