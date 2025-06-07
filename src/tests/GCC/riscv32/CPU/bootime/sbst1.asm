/*
*   your amazing test header 
*   your amazing test header 
*   your amazing test header 
*   your amazing test header 
*   your amazing test header 
*   Author(s):
*   last modified date:
*   description: 
*       Intrusive/non-Intrusive 
*       description of test setup 
*       general requirements 
*       precondition/postconditions 
*       
*/

  SBST_ALIGNMENT
  .section STL_BT_CODE // this could also become a define for example #define STL_TEXT_SECTION ".text_stl"
  .globl sbst1

  /*
    for example 
    extern SIGNATURE_T test_rt_adder1(void); // prototype
    
    test_rt_adder1 is a runtime sbst for the adder     
    it returns a SIGNATURE_T (commonly an uint32 data type) to the OS 

    // in the main 
    sig=test_rt_adder1();
  */

    // here you may add additional local routines and macros 
    // common used macros could be into a shared file among the sbsts

sbst1:

////////////////
// sbst start //
////////////////


//////////////////
// abi prologue //
//////////////////
// see stack_frame_layout.md or verbosily write the stack layout here 

RISCV_ABI_PROLOGUE // this could be a macro 

////////////////////////////
// test setup (if needed) //
////////////////////////////
// initialize register and variables as needed 

/////////////////////////
// my sbst core start  //
/////////////////////////




/////////////////////////
// my sbst core end    //
/////////////////////////





////////////////////////////////////////////////////
// signature computation and function return     //
///////////////////////////////////////////////////

    COMPUTE_SIGNATURE // this could be a macro (called verbosily at every operation in the sbst core)

    CHECK_SIGNATURE 


//////////////////
// abi epilogue //
//////////////////
    RISCV_ABI_EPILOGUE // this could be a macro 


////////////////
// sbst end   //
////////////////

//jump to link register


/////////////////////////
// sbst-related areas  //
/////////////////////////

SBST_ALIGNMENT // this could be a macro 
.section STL_RODATA 
TEST_ID_SBST1:          .dword 0x1
GOLDEN_SIGNATURE:       .dword 0xcafecafe

.section STL_DATA // the section name can be defined into an header file 
SIGN: .dword 0
