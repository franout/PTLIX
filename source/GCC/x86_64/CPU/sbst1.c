
#include "stl_types.h"

#define TEST_DATA_LENGHT 32
const test_data_patterns[] = {

};

SIGNATURE_T test_adder(void)
{

    /* a very simple test for the integer addition */
    SIGNATURE_T sig = 0;
    int i;
    int a, b, c;
    
    for (i = 0; i < TEST_DATA_LENGHT; i++)
    {
        a = test_data_patterns[i];
        b = test_data_patterns[i];
        c = a + b;
        sig |= c;
    }
    return sig;
}