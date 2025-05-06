#ifndef __STL_CFG_H__
#define __STL_CFG_H__

#ifndef __STL__
/**
 * Define for enabling compilation of Software Test Library.
 * Note: It must be defined at compiler level.
*/
#define __STL__								1u
#endif /*__STL__*/


/************************ Compiler Dependent directives ************************/
/** 
 *   Assembly keyword for Extended assembly.
 */
#define ASM_KEYWORD(x) asm volatile(x) 

/**
 * \defgroup Linker dependent sections.
 * Section definition for library (they must be instantiated in the linker script)
 * 
 * Note: If not defines in the linker script, the STL goes to the end of all the other sections
 */
/**@{*/

#define STL_BOOT_TEST_IVOR_SECTION ".stl_bt_ivor"

/*definition of test code section and data*/
#define STL_CODE_BOOTIME_SECTION ".stl_bt_code"
#define STL_DATA_BOOTIME_SECTION ".stl_bt_data"

#define STL_CODE_RUNTIME_SECTION ".stl_rt_code"
#define STL_DATA_RUNTIME_SECTION ".stl_rt_code"

#define STL_TEST_HEADER_SECTION ".stl_test_header_section"

#define STL_SIGNATURE_SECTION ".stl_rt_code"

#define STL_CODE_SECTION_MODIFIED_IVOR ".text_vle"
#define STL_CODE_SECTION_MODIFIED_HANDLERS ".text_vle"
/**@}*/


/*****************************************************************************************************/
/****************                         Scheduler services                          ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_TEST_CHUNK_SIZE                     1u


/** 
 *  Note Scheduler type:
 *                       - 0 Sequential SBST scheduler
 *                       - 1 Not implemented
 *                       - 2 Not implemented
*/
#define STL_SCHEDULER_TYPE                      0u 

/*****************************************************************************************************/
/****************                    Test Setup Support Package                       ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_OS_PRESENT					        0u 

#define STL_MULTICORE_SOC                       0u

#if (STL_MULTICORE_SOC > 0u)
    #define STL_MULTICORE_EXECUTION 		    0u 
#endif /*STL_MULTICORE_SOC*/

/*****************************************************************************************************/
/****************                    Software-Self Tests                              ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_BOOT_TEST 		                    0u 
#define STL_RUNTIME_TEST 	                    0u 


/*************************** Signature related defines ***********************************************/
//TODO signature mismatch
/*! mismatch value if cocmputed signature is different from the golden signature*/
#define STL_SIGNATURE_MISMATCH 		0x01010101

// TODO change polito spyaddr and test code ram base
#define POLITO_SPYADDR  __stl_polito_spy_addr__
#define TEST_CODE_RAM_BASE __stl_TEST_CODE_RAM_BASE__

#define STL_RELOCATED 					0u  //TODO verify relocation
#define STL_RELOCATION_TABLE			0u

/*****************************************************************************************************/
/****************                    Error Management                                 ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_ERROR_MANAGEMENT_ENABLED	1u 
#define STL_ERROR_MANAGEMENT_VERBOSE    0u 




#endif /* __STL_CFG_H__ */
