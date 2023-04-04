// #include "unity.h"
// #include "ballmover.h"
// #include "matrixhelper.h"
// #include "testingutils.h"

// MatrixHelper _helper;
// BallMover _ballMover(&_helper, 10, 10);

// void AssertBallAt(MatrixSnapshot *snapshot, int x, int y);
// void SetBallDx(int dx);
// void SetBallDy(int dy);

// void CanGetSnapshot()
// {
//     auto snapshot = _ballMover.GetSnapshot();

//     TEST_ASSERT_NOT_NULL(snapshot);
//     TEST_ASSERT_EQUAL_INT32(100, snapshot->totalCells);
//     TEST_ASSERT_NOT_NULL(snapshot->cells);
//     AssertBallAt(snapshot, 0, 0);
//     AssertEmptyCells(snapshot, 99);
// }

// void CanSetBall()
// {
//     _ballMover.SetBall(1, 1);

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertEmptyCells(snapshot, 99);
//     AssertBallAt(snapshot, 1, 1);
// }

// void CanMoveBall()
// {
//     _ballMover.SetBall(0, 0);
//     SetBallDx(1);
//     SetBallDy(1);

//     _ballMover.Move();
//     _ballMover.Move();
//     _ballMover.Move();

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertEmptyCells(snapshot, 99);
//     AssertBallAt(snapshot, 3, 3);
// }

// void MoveBall_WhenBottom()
// {
//     _ballMover.SetBall(0, 9);
//     SetBallDx(1);
//     SetBallDy(1);

//     _ballMover.Move();

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertBallAt(snapshot, 1, 8);
// }

// void MoveBall_WhenTop()
// {
//     _ballMover.SetBall(1, 0);
//     SetBallDx(1);
//     SetBallDy(-1);

//     _ballMover.Move();

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertBallAt(snapshot, 2, 1);
// }

// void MoveBall_WhenRight()
// {
//     _ballMover.SetBall(9, 1);
//     SetBallDx(1);
//     SetBallDy(1);

//     _ballMover.Move();

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertBallAt(snapshot, 8, 2);
// }

// void MoveBall_WhenLeft()
// {
//     _ballMover.SetBall(0, 1);
//     SetBallDx(-1);
//     SetBallDy(1);

//     _ballMover.Move();

//     auto snapshot = _ballMover.GetSnapshot();
//     AssertBallAt(snapshot, 1, 2);
// }

// void CanReverseDx()
// {
//     auto first = _ballMover.ReverseDx();
//     auto next = _ballMover.ReverseDx();

//     TEST_ASSERT_NOT_EQUAL(0, first);
//     TEST_ASSERT_EQUAL_INT(first, -next);
// }

// void CanReverseDy()
// {
//     auto first = _ballMover.ReverseDy();
//     auto next = _ballMover.ReverseDy();

//     TEST_ASSERT_NOT_EQUAL(0, first);
//     TEST_ASSERT_EQUAL_INT(first, -next);
// }

// void AssertBallAt(MatrixSnapshot *snapshot, int x, int y)
// {
//     auto index = _helper.GetMatrixIndex(x, y);
//     TEST_ASSERT_LESS_THAN(100, index);
//     TEST_ASSERT_EQUAL_INT8(1, snapshot->cells[index]);
// }

// void SetBallDx(int dx)
// {
//     auto newDx = _ballMover.ReverseDx();
//     if (newDx != dx)
//     {
//         _ballMover.ReverseDx();
//     }
// }

// void SetBallDy(int dy)
// {
//     auto newDy = _ballMover.ReverseDy();
//     if (newDy != dy)
//     {
//         _ballMover.ReverseDy();
//     }
// }


// int main()
// {
//     UNITY_BEGIN();

//     RUN_TEST(CanGetSnapshot);
//     RUN_TEST(CanSetBall);
//     RUN_TEST(CanMoveBall);
//     RUN_TEST(MoveBall_WhenBottom);
//     RUN_TEST(MoveBall_WhenTop);
//     RUN_TEST(MoveBall_WhenRight);
//     RUN_TEST(MoveBall_WhenLeft);

//     RUN_TEST(CanReverseDx);
//     RUN_TEST(CanReverseDy);

//     UNITY_END();
//     return 0;
// }
