#if __STL__

#ifndef __STL_H__
#define __STL_H__

/**
 * @file stl.h
 * @brief STL API header file.
 * This file contains the declarations for the STL API functions and types.
 * It is part of the STL (Software Test Library) module.
 * This file should be included in the source files that need to use the STL API.
 * It provides the necessary function prototypes and type definitions for the STL functionality.
 * It is designed to be used in conjunction with the STL configuration and types headers.
 * It is intended for use in embedded systems and applications that require online testing capabilities.
 * It includes functions for initialization, deinitialization, scheduling tests, and error management.
 * It also includes definitions for error handling and test management.
 * @note This file is part of the STL module and should be used in accordance with the STL configuration.
 */

/**
 * @defgroup STL STL API
 * @brief Software Test Library (STL) API.
 * This module provides an API for the Software Test Library (STL).
 * It includes functions for initializing the STL, scheduling tests, and managing errors.
 * It is designed to be used in embedded systems and applications that require online testing capabilities.
 * @ingroup STL
 */
#include "stl_cfg.h"
#include "stl_tssp.h"
#include "stl_types.h"

/**
 * @brief Failed test structure.
 * This structure is used to represent a failed test in the STL.
 * It contains the index of the test and its signature.
 * The index is used to identify the test, and the signature is used to verify the test's integrity.
 * It is used in error management to track failed tests.
 * @note This structure is part of the STL error management system.
 * @ingroup STL
 * @struct STL_FAILED_TEST_T
 * @var STL_FAILED_TEST_T::index
 */
typedef struct
{
	STL_INT32U_T index;
	STL_SIGNATURE_T signature;
} STL_FAILED_TEST_T;

/**
 * @brief STL API function declarations.
 * This section contains the function declarations for the STL API.
 * These functions are used to initialize and deinitialize the STL,
 * schedule runtime and boot-time tests,
 * and manage errors.
 * They are part of the STL module and should be used in accordance with the STL configuration.
 * @ingroup STL
 * @defgroup STL_API STL API Functions
 * @brief Functions for STL API.
 * This group contains the function declarations for the STL API.
 * These functions are used to initialize and deinitialize the STL,
 * schedule runtime and boot-time tests,
 * and manage errors.
 * They are part of the STL module and should be used in accordance with the STL configuration.
 * @{
 * API Functions
 * @ingroup STL_API
 */

/**
 * STL_init
 * @brief Initializes the STL.
 * This function initializes the Software Test Library (STL) by setting up the necessary data structures and error
 * management. It should be called before any other STL functions are used.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during initialization.
 * @return void
 * @note This function must be called before using any other STL functions.
 * It initializes the STL error management system and prepares the library for use.
 * @ingroup STL_API
 * @see STL_deinit
 */
STLLIB_PUBLIC void STL_init(STL_ERROR_T *err);
/**
 * @brief Deinitializes the STL.
 * This function deinitializes the Software Test Library (STL) by cleaning up resources and error management.
 * It should be called when the STL is no longer needed, typically at the end of the program or before reinitialization.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during deinitialization.
 * @return void
 * @note This function cleans up the STL error management system and releases any resources allocated during
 * initialization. It is important to call this function to ensure that all resources are properly released and no
 * memory leaks occur.
 * @ingroup STL_API
 * @see STL_init
 * @note This function should be called after all STL tests have been executed and before the program terminates.
 * It ensures that all resources are properly released and the STL is in a clean state for future use.
 */
STLLIB_PUBLIC void STL_deinit(STL_ERROR_T *err);

/**
 * @brief Schedules runtime tests for a specific CPU.
 * This function schedules the runtime tests for the specified CPU.
 * It is used to execute the tests that are defined in the STL for runtime verification.
 * @param cpu The CPU for which the runtime tests are to be scheduled.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during scheduling.
 * @return void
 * @note This function is part of the STL runtime testing framework.
 * It is used to schedule tests that are executed during the runtime of the system.
 */
STLLIB_PUBLIC void STL_schedule_runtime(STL_CPUS cpu, STL_ERROR_T *err);
/**
 * @brief Schedules boot-time tests for a specific CPU.
 * This function schedules the boot-time tests for the specified CPU.
 * It is used to execute the tests that are defined in the STL for boot-time verification.
 * @param cpu The CPU for which the boot-time tests are to be scheduled.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during scheduling.
 * @return void
 * @note This function is part of the STL boot-time testing framework.
 * It is used to schedule tests that are executed during the boot process of the system.
 * It is typically called during the system initialization phase.
 */
STLLIB_PUBLIC void STL_schedule_bootime(STL_CPUS cpu, STL_ERROR_T *err);

#if STL_RELOCATED
/**
 * @brief Relocates runtime tests.
 * This function relocates the runtime tests to the appropriate memory locations.
 * It is used to ensure that the tests are correctly positioned in memory for execution.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during relocation.
 * @return void
 * @note This function is part of the STL relocation process.
 * It is used to adjust the memory addresses of the runtime tests after relocation.
 * @see STL_init
 */
STLLIB_PUBLIC void STL_relocate_runtime_tests(STL_ERROR_T *err);
#endif /*__STL_RELOCATED__*/

#if STL_OS_PRESENT
/**
 * @brief Creates an OS task for the STL runtime tests.
 * This function creates a task in the operating system for executing the STL runtime tests.
 * It is used to run the tests in a separate task context, allowing for concurrent execution with other system tasks.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during task creation.
 * @return void
 * @note This function is part of the STL OS integration.
 * It is used to create a task that will execute the runtime tests in an operating system environment.
 */
STLLIB_PUBLIC void STL_runtime_OS_task_create(STL_ERROR_T *err);

/**
 * @brief Deletes the OS task for the STL runtime tests.
 * This function deletes the task in the operating system that was created for executing the STL runtime tests.
 * It is used to clean up the task when it is no longer needed, typically at the end of the testing process.
 * @param err Pointer to an STL_ERROR_T variable to store any error that occurs during task deletion.
 * @return void
 * @note This function is part of the STL OS integration.
 * It is used to remove the task that was created for executing the runtime tests in an operating system environment.
 * It should be called when the tests are complete or when the system is shutting down.
 */
STLLIB_PUBLIC void STL_runtime_OS_task_delete(STL_ERROR_T *err);
#endif /*__STL_IN_OS__*/

#if STL_ERROR_MANAGEMENT_ENABLED


/**
 * @brief Initializes the error management system.
 *
 * @param err Pointer to the error structure to initialize.
 */
STLLIB_PUBLIC EXTERN_KEYWORD void STL_em_init(STL_ERROR_T *err);

/**
 * @brief Deinitializes the error management system.
 *
 * @param err Pointer to the error structure to initialize.
 */
STLLIB_PUBLIC EXTERN_KEYWORD void STL_em_deinit(STL_ERROR_T *err);
/**
 * @brief Handles a runtime failure for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param err Pointer to the error structure to update.
 * @return The size of the runtime failure data.
 */
STLLIB_PUBLIC EXTERN_KEYWORD STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu, STL_ERROR_T *err);

/**
 * @brief Handles all runtime failures for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param vect Pointer to the vector of failed tests.
 * @param err Pointer to the error structure to update.
 */
STLLIB_PUBLIC EXTERN_KEYWORD void STL_em_failed_runtime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err);

/**
 * @brief Handles all boot-time failures for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param vect Pointer to the vector of failed tests.
 * @param err Pointer to the error structure to update.
 */
STLLIB_PUBLIC EXTERN_KEYWORD void STL_em_failed_bootime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err);

/**
 * @brief Retrieves the boot-time signature for a specific CPU and index.
 *
 * @param cpu The CPU identifier.
 * @param index The index of the signature to retrieve.
 * @param err Pointer to the error structure to update.
 * @return The boot-time signature.
 */
STLLIB_PUBLIC EXTERN_KEYWORD STL_SIGNATURE_T STL_em_bt_get_signature(STL_CPUS cpu, STL_SIZE_T index, STL_ERROR_T *err);

/**
 * @brief Retrieves the runtime signature for a specific CPU and index.
 *
 * @param cpu The CPU identifier.
 * @param index The index of the signature to retrieve.
 * @param err Pointer to the error structure to update.
 * @return The runtime signature.
 */
STLLIB_PUBLIC EXTERN_KEYWORD STL_SIGNATURE_T STL_em_rt_get_signature(STL_CPUS cpu, STL_SIZE_T index, STL_ERROR_T *err);

#endif /*STL_ERROR_MANAGEMENT_ENABLED*/

#endif /* __STL_H__ */
#endif /*__STL__*/