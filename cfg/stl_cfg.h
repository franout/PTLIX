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

#define STL_CODE_SECTION_MODIFIED_EXCEPTION ".stl_exception_table"
#define STL_CODE_SECTION_MODIFIED_HANDLERS ".stl_exception_handlers"
/**@}*/


/*****************************************************************************************************/
/****************                         Scheduler services                          ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_TEST_CHUNK_SIZE                     1u


/** 
 *  Note Scheduler type:
 *                       - 0 Sequential SBST scheduler (for runtime tests only)
 *                       - 1 Chunk-based SBST scheduler (for runtime tests only)
 *                       - 2 Not implemented
*/
#define STL_SCHEDULER_TYPE                      0u 

/*****************************************************************************************************/
/****************                    Test Setup Support Package                       ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_OS_PRESENT					        0u 

#define STL_MULTICORE_SOC                       0u


/* CPU related*/
#if (STL_MULTICORE_SOC > 0u)
    #define STL_MULTICORE_EXECUTION 		    0u 
    #define STL_NUM_CPU                         2u 
    #define STL_USE_MPU                         0u /* Use the memory protection unit */
#endif /*STL_MULTICORE_SOC*/


#define STL_USE_WATCHDOG                        0u /* Use the watchdog for test execution */
#define STL_USE_FINE_GRAINED_WATCHDOG           0u /* Use the fine grained watchdog for test execution (defined for each test in the STL) */
#if (STL_USE_WATCHDOG > 0u && STL_USE_FINE_GRAINED_WATCHDOG == 0u)
    #define STL_WATCHDOG_TIMEOUT                0x00000000u /* Watchdog timeout value */
    #define STL_WATCHDOG_RESET_VALUE            0u /* Watchdog reset value */
#endif /*STL_USE_WATCHDOG*/

/* CSP related*/
#define STL_
/* OS related*/
#if (STL_OS_PRESENT > 0u)
    #define STL_OS_RT_TASK_STACK_SIZE          0x00000000u /* Stack size for the OS task */
    #define STL_OS_RT_TASK_PRIORITY            0u /* Task priority for the OS task */
    #define STL_OS_RT_TASK_PERIOD              0u /* Task period for the OS task */
    #define STL_OS_RT_TASK_CRC                 0u /* Compute CRC for the OS task in charge of executing the STL */
#endif /* SLT_OS_PRESENT */

/*****************************************************************************************************/
/****************                    Software-Self Tests                              ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_BOOT_TEST 		                    0u 
#define STL_RUNTIME_TEST 	                    0u 


/*****************************************************************************************************/
/*************************** Signature related defines ***********************************************/
/*****************************************************************************************************/
/*! mismatch value if cocmputed signature is different from the golden signature*/
#define STL_SIGNATURE_MISMATCH 		0x01010101


/*****************************************************************************************************/
/*************************** Relocation related defines **********************************************/
/*****************************************************************************************************/

#define STL_RELOCATED 					0u  //TODO verify relocation
#define STL_RELOCATION_TABLE			0u  /* Relocation table for multiple relocations */

/*****************************************************************************************************/
/****************                    Error Management                                 ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_ERROR_MANAGEMENT_ENABLED	1u 
#define STL_ERROR_MANAGEMENT_VERBOSE    0u 




#endif /* __STL_CFG_H__ */
