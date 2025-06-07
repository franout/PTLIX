#include "stl.h"
#include "stl_types.h"


int main (void){
    STL_ERROR_T err;
    STL_SIGNATURE_T signature = 0; // Initialize the signature variable

    STL_init(&err);
    if (err != STL_ERROR_NONE) {
        // Handle initialization error
        return -1;
    }
    STL_schedule_runtime(0,&err);
    if (err != STL_ERROR_NONE) {
        // Handle scheduling error
        return -1;
    }   
    STL_em_rt_get_signature(0, 0, &err);
    if (err != STL_ERROR_NONE) {
        // Handle error in getting signature
        return -1;
    }
}