
#include "stl_types.h"

#define TEST_DATA_LENGTH 32
const int test_data_patterns[] = {
    0x00000001, 0x00000002, 0x00000003, 0x00000004,
    0x00000005, 0x00000006, 0x00000007, 0x00000008,
    0x00000009, 0x0000000A, 0x0000000B, 0x0000000C,
    0x0000000D, 0x0000000E, 0x0000000F, 0x00000010,
    0x11111111, 0x22222222, 0x33333333, 0x44444444,
    0x55555555, 0x66666666, 0x77777777, 0x88888888,
    0x99999999, 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC,
    0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF, 0x00000000
};

STL_SIGNATURE_T test_adder(void)
{

    /* a very simple test for the integer addition */
    STL_SIGNATURE_T sig = 0;
    int i;
    int a, b, c;
    
    for (i = 0; i < TEST_DATA_LENGTH; i++)
    {
        a = test_data_patterns[i];
        b = test_data_patterns[i];
        c = a + b;
        sig |= c;
    }
    return sig;
}