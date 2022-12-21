#include "testingutils.h"
#include "matrixhelper.h"
#include "..\lib\mocks\mockDatetimeprovider.h"
#include "effects\scanner.h"

int main()
{
    MatrixHelper helper;
    MockDateTimeProvider mockDateTimeProvider;
    Scanner scanner(&mockDateTimeProvider, &helper, 10, 10);
    scanner.SetDelayMs(0);

    // for (size_t i = 0; i < 22; i++)
    // {
    //     DrawMatrix(scanner.GetSnapshot());
    //     scanner.Move();
    // }
}
