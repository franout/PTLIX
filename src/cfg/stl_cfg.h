/**
 * @file stl_cfg.h
 * @brief Configuration header for the Software Test Library (STL).
 *
 * This file contains configuration macros and definitions for enabling and
 * customizing the Software Test Library (STL). It includes compiler-dependent
 * directives, linker section definitions, scheduler services, test setup
 * support, and error management configurations.
 *
 * @note The macro `__STL__` must be defined at the compiler level to enable
 *       compilation of the STL.
 *
 * @section CompilerDirectives Compiler Dependent Directives
 * - Defines keywords for extended assembly, weak symbols, static, and inline
 *   based on the compiler being used.
 * - Issues a warning if the compiler is not recognized.

 * @section LinkerSections Linker Dependent Sections
 * - Defines custom linker sections for STL boot-time and runtime code, data,
 *   and exception handlers.
 * - These sections must be instantiated in the linker script.

 * @section SchedulerServices Scheduler Services
 * - Defines the chunk size and scheduler type for runtime tests.
 * - Scheduler types:
 *   - 0: Sequential SBST scheduler (runtime tests only).
 *   - 1: Chunk-based SBST scheduler (runtime tests only).
 *   - 2: Custom scheduler (user-defined).

 * @section TestSetup Test Setup Support Package
 * - Configures options for OS presence, multicore SoC, memory protection unit
 *   (MPU), and watchdog usage.
 * - Includes settings for OS task stack size, priority, period, and CRC.

 * @section SoftwareSelfTests Software-Self Tests
 * - Enables or disables boot-time and runtime tests.

 * @section Signature Signature Related Defines
 * - Defines the mismatch value for signature verification.

 * @section Relocation Relocation Related Defines
 * - Configures relocation settings and relocation table usage.

 * @section ErrorManagement Error Management
 * - Enables or disables error management and verbose error reporting.

 * @section ErrorCheck Error Check
 * - Ensures at least one test type (boot-time or runtime) is selected.
 *
 * @warning If no tests are selected, a compilation error will occur.
 */
#ifndef __STL_CFG_H__
#define __STL_CFG_H__

#ifndef __STL__
/**
 * Define for enabling compilation of Software Test Library.
 * Note: It must be defined at compiler level.
 */
#define __STL__ 1u
#endif /*__STL__*/

/************************ Compiler Dependent directives ************************/
/**
 *   Assembly keyword for Extended assembly.
 */
#if defined(__GNUC__) || defined(__clang__)
#define ASM_KEYWORD(x) asm volatile(x)
#define WEAK_KEYWORD __attribute__((weak))
#define STATIC_KEYWORD static
#define INLINE_KEYWORD inline
#define EXTERN_KEYWORD extern
#else
#warning "Compiler keyword not defined. Please check the compiler documentation."
#endif /*defined(__GNUC__) || defined(__clang__)*/
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

#define STL_TEST_CHUNK_SIZE 1u

/**
 *  Note Scheduler type:
 *                       - 0 Sequential SBST scheduler (for runtime tests only)
 *                       - 1 Chunk-based SBST scheduler (for runtime tests only)
 *                       - 2 Custom (overwrite the definition)
 */
#define STL_SCHEDULER_TYPE 0u

/*****************************************************************************************************/
/****************                    Test Setup Support Package                       ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_OS_PRESENT 0u

#define STL_MULTICORE_SOC 0u

/* CPU related*/
#if (STL_MULTICORE_SOC > 0u)
#define STL_MULTICORE_EXECUTION 1u
#define STL_USE_MPU 0u /* Use the memory protection unit */
#else
#define STL_MULTICORE_EXECUTION 0u
#define STL_USE_MPU 0u /* Use the memory protection unit */
#endif				   /*STL_MULTICORE_SOC*/

/* CSP related*/
#define STL_USE_WATCHDOG 0u /* Use the watchdog for test execution */
#define STL_USE_FINE_GRAINED_WATCHDOG                                                                                  \
	0u /* Use the fine grained watchdog for test execution (defined for each test in the STL) */
#if (STL_USE_WATCHDOG > 0u && STL_USE_FINE_GRAINED_WATCHDOG == 0u)
#define STL_WATCHDOG_TIMEOUT 0x00000000u /* Watchdog timeout value */
#define STL_WATCHDOG_RESET_VALUE 0u		 /* Watchdog reset value */
#endif									 /*STL_USE_WATCHDOG*/

/* OS related*/
#if (STL_OS_PRESENT > 0u)
#define STL_OS_RT_TASK_STACK_SIZE 0x00000000u /* Stack size for the OS task */
#define STL_OS_RT_TASK_PRIORITY 0u			  /* Task priority for the OS task */
#define STL_OS_RT_TASK_PERIOD 0u			  /* Task period for the OS task */
#define STL_OS_RT_TASK_CRC 0u				  /* Compute CRC for the OS task in charge of executing the STL */
#endif										  /* STL_OS_PRESENT */

/*****************************************************************************************************/
/****************                    Software-Self Tests                              ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#ifndef STL_BOOT_TEST
#define STL_BOOT_TEST 0u
#endif /*STL_BOOT_TEST*/
#ifndef STL_RUNTIME_TEST
#define STL_RUNTIME_TEST 0u
#endif /*STL_RUNTIME_TEST*/

/*****************************************************************************************************/
/*************************** Signature related defines ***********************************************/
/*****************************************************************************************************/
/*! mismatch value if cocmputed signature is different from the golden signature*/
#define STL_SIGNATURE_MISMATCH 0x01010101

/*****************************************************************************************************/
/*************************** Relocation related defines **********************************************/
/*****************************************************************************************************/

#define STL_RELOCATED 0u		 /* Relocation is enabled */
#define STL_RELOCATION_TABLE 0u /* Relocation table for multiple relocations */

/*****************************************************************************************************/
/****************                  Error Management Module                            ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#define STL_ERROR_MANAGEMENT_ENABLED 1u
#define STL_ERROR_MANAGEMENT_VERBOSE 0u

/*****************************************************************************************************/
/****************                    Error Check                                      ****************/
/****************                                                                     ****************/
/*****************************************************************************************************/

#if (STL_BOOT_TEST == 0u && STL_RUNTIME_TEST == 0u)
#error "No tests selected. Please select at least one test type."
#endif

#endif /* __STL_CFG_H__ */
