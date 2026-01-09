#pragma once

class MatrixHelper
{
    int _width = 10;
    int _height = 10;
    int _totalLeds = 100;

public:
    MatrixHelper();
    bool IsReversedRow(int row) const;
    int GetMatrixIndex(int x, int y) const;
};

inline MatrixHelper::MatrixHelper()
{
    _totalLeds = _width * _height;
}

inline int MatrixHelper::GetMatrixIndex(int x, int y) const
{
    int offset = x * _height;

    if (IsReversedRow(x))
    {
        return _totalLeds - ((x + 1) * _height) + (_height - y) - 1;
    }

    return _totalLeds - offset - (_height - y);
}

inline bool MatrixHelper::IsReversedRow(int row) const
{
    return (_width - row) % 2 == 0;
}
