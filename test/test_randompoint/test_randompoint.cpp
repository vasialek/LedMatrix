#include "unity.h"
#include "effects\randompoint.h"

RandomPoint _randomPoint;

void CanRandomPoint()
{
    auto actual = _randomPoint.SwitchNextColor();

    TEST_ASSERT_EQUAL_INT32(2, actual);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(CanRandomPoint);

    UNITY_END();
}
