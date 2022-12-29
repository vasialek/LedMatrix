#pragma once

// #include <iostream>
#include "unity.h"
#include "acolors.h"
#include "matrixhelper.h"
#include "matrixsnapshot.h"

MatrixHelper _testingUtilsHelper;

char _getMatrixColorSymbol(unsigned char symbol);

void AssertEmptyCells(MatrixSnapshot *snapshot, int expected)
{
    int emptyCells = 0;
    for (size_t i = 0; i < snapshot->totalCells; i++)
    {
        if (snapshot->cells[i] == 0)
        {
            emptyCells++;
        }
    }

    TEST_ASSERT_EQUAL_INT(expected, emptyCells);
}

void AssertZeroAt(MatrixSnapshot *snapshot, int x, int y)
{
    auto index = _testingUtilsHelper.GetMatrixIndex(x, y);
    TEST_ASSERT_LESS_THAN(100, index);
    TEST_ASSERT_EQUAL(0, snapshot->cells[index]);
}

void AssertNonZeroAt(MatrixSnapshot *snapshot, int x, int y)
{
    auto index = _testingUtilsHelper.GetMatrixIndex(x, y);
    TEST_ASSERT_LESS_THAN(100, index);
    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, snapshot->cells[index], "Expected non-zero value");
}

void DrawMatrix(MatrixSnapshot *snapshot)
{
    // int index = 0;
    // std::cout << "--------------------\n";
    // for (size_t y = 0; y < 10; y++)
    // {
    //     for (size_t x = 0; x < 10; x++)
    //     {
    //         index = _testingUtilsHelper.GetMatrixIndex(x, y);
    //         // std::cout << (snapshot->cells[index] == 0 ? "o" : "x") << " ";
    //         std::cout << _getMatrixColorSymbol(snapshot->cells[index]) << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

char _getMatrixColorSymbol(unsigned char symbol)
{
    switch (symbol)
    {
    case ACOLOR_OFF:
        return 'o';
    case ACOLOR_RED:
        return 'r';
    case ACOLOR_GREEN:
        return 'g';
    case ACOLOR_BLUE:
        return 'b';
    
    default:
        return 'x';
    }
}
