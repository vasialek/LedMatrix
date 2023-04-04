// #include "unity.h"
// #include "matrixhelper.h"

// MatrixHelper _helper;

// void test_get_0_0()
// {
//     int actual = _helper.GetMatrixIndex(0, 0);

//     TEST_ASSERT_EQUAL_INT32(99, actual);
// }

// void test_get_0_9()
// {
//     int actual = _helper.GetMatrixIndex(0, 9);

//     TEST_ASSERT_EQUAL_INT32(90, actual);
// }

// void test_get_9_0()
// {
//     int actual = _helper.GetMatrixIndex(9, 0);

//     TEST_ASSERT_EQUAL_INT32(0, actual);
// }

// void test_get_9_9()
// {
//     int actual = _helper.GetMatrixIndex(9, 9);

//     TEST_ASSERT_EQUAL_INT32(9, actual);
// }

// void test_get_8_9()
// {
//     int actual = _helper.GetMatrixIndex(8, 9);

//     TEST_ASSERT_EQUAL_INT32(10, actual);
// }

// void test_is_not_reversed()
// {
//     for (size_t i = 1; i < 10; i += 2)
//     {
//         bool actual = _helper.IsReversedRow(9);

//         TEST_ASSERT_FALSE(actual);
//     }
// }

// void test_is_reversed()
// {
//     for (size_t i = 0; i < 9; i += 2)
//     {
//         bool actual = _helper.IsReversedRow(8);

//         TEST_ASSERT_TRUE(actual);
//     }
    
// }

// int main()
// {
//     UNITY_BEGIN();

//     RUN_TEST(test_is_reversed);
//     RUN_TEST(test_is_not_reversed);

//     RUN_TEST(test_get_9_0);
//     RUN_TEST(test_get_9_9);
//     RUN_TEST(test_get_0_0);
//     RUN_TEST(test_get_0_9);
//     RUN_TEST(test_get_8_9);

//     UNITY_END();
// }
