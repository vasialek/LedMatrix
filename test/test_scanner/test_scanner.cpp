#include "unity.h"
#include "matrixhelper.h"
#include "testingutils.h"
#include "..\lib\mocks\mockDatetimeprovider.h"
#include "effects\scanner.h"

MatrixHelper _helper;
MockDateTimeProvider mockDateTimeProvider;
Scanner _scanner(&mockDateTimeProvider, &_helper, 10, 10);

void CanScanner()
{
    auto snapshot = _scanner.GetSnapshot();

    AssertEmptyCells(snapshot, 90);
}

void Reset_CheckAtTop()
{
    auto snapshot = _scanner.GetSnapshot();

    AssertNonZeroAt(snapshot, 0, 0);
    AssertNonZeroAt(snapshot, 2, 0);
    AssertNonZeroAt(snapshot, 4, 0);
    AssertNonZeroAt(snapshot, 6, 0);
    AssertNonZeroAt(snapshot, 8, 0);
}

void Reset_CheckAtBottom()
{
    auto snapshot = _scanner.GetSnapshot();

    AssertNonZeroAt(snapshot, 1, 9);
    AssertNonZeroAt(snapshot, 3, 9);
    AssertNonZeroAt(snapshot, 5, 9);
    AssertNonZeroAt(snapshot, 7, 9);
    AssertNonZeroAt(snapshot, 9, 9);
}

void CanMove()
{
    _scanner.Reset();

    _scanner.Move();

    auto snapshot = _scanner.GetSnapshot();
    AssertZeroAt(snapshot, 0, 0);
    AssertNonZeroAt(snapshot, 0, 1);
    AssertZeroAt(snapshot, 1, 9);
    AssertNonZeroAt(snapshot, 1, 8);
}

void Move_ReverseAtBottom()
{
    _scanner.Reset();
    for (size_t i = 0; i < 9; i++)
    {
        _scanner.Move();    // Move to bottom
    }
    
    _scanner.Move();

    auto snapshot = _scanner.GetSnapshot();
    AssertZeroAt(snapshot, 0, 9);
    AssertNonZeroAt(snapshot, 0, 8);
}

void Move_ReverseAtTop()
{
    _scanner.Reset();
    for (size_t i = 0; i < 9; i++)
    {
        _scanner.Move();    // Move to top
    }

    _scanner.Move();

    auto snapshot = _scanner.GetSnapshot();
    AssertZeroAt(snapshot, 1, 0);
    AssertNonZeroAt(snapshot, 1, 1);
}

void Move_DoNotMove_WhenTooEarly()
{
    _scanner.Reset();
    _scanner.SetDelayMs(500);
    
    _scanner.Move();
    _scanner.Move();  // this should be skipped

    auto snapshot = _scanner.GetSnapshot();
    AssertNonZeroAt(snapshot, 0, 1);
}

void CanSwitchNextColor()
{
    _scanner.Reset();

    _scanner.SwitchNextColor();
    auto actual = _scanner.SwitchNextColor();

    TEST_ASSERT_EQUAL_INT32(3, actual);
}

void SwitchNextColor_GoToFirstColor_WhenOverwlow()
{
    _scanner.Reset();
    for (size_t i = 0; i < ACOLOR_MAX - 1; i++)
    {
        _scanner.SwitchNextColor();
    }

    auto actual = _scanner.SwitchNextColor();

    TEST_ASSERT_EQUAL_INT32(ACOLOR_MIN, actual);
}

int main()
{
    _scanner.SetDelayMs(0);
    mockDateTimeProvider.SetNextMillis(1000);

    UNITY_BEGIN();

    // RUN_TEST(CanScanner);
    // RUN_TEST(Reset_CheckAtTop);
    // RUN_TEST(Reset_CheckAtBottom);
    // RUN_TEST(CanMove);
    // RUN_TEST(Move_ReverseAtBottom);
    // RUN_TEST(Move_ReverseAtTop);
    // RUN_TEST(Move_DoNotMove_WhenTooEarly);
    RUN_TEST(CanSwitchNextColor);
    RUN_TEST(SwitchNextColor_GoToFirstColor_WhenOverwlow);

    UNITY_END();
}

