/**
 * @file stl_scheduler.c
 * @brief Implementation of the STL (Self-Test Library) scheduler for boot-time and runtime tests.
 *
 * This file contains the implementation of the STL scheduler, which is responsible for
 * scheduling and executing self-tests during boot-time and runtime. The scheduler supports
 * both single-core and multi-core configurations and provides different scheduling strategies
 * such as sequential, chunk-based, and custom schedulers.
 *
 * The following features are implemented:
 * - Boot-time test scheduling
 * - Runtime test scheduling
 * - Support for single-core and multi-core systems
 * - Configurable scheduling strategies
 *
 * @note The scheduler behavior is controlled by preprocessor macros defined in the configuration
 *       header files. Ensure that the configuration is properly set before using this module.
 *
 * @details
 * ### Boot-Time Scheduler
 * The boot-time scheduler executes self-tests sequentially during the system boot process.
 * It ensures that all tests are executed in a predefined order and updates the test signatures
 * accordingly. The scheduler can be configured for single-core or multi-core systems.
 *
 * ### Runtime Scheduler
 * The runtime scheduler executes self-tests during the system's runtime. It supports three
 * scheduling strategies:
 * - Sequential: Executes all runtime tests sequentially.
 * - Chunk-based: Executes runtime tests in chunks, allowing partial execution in each cycle.
 * - Custom: Allows the user to implement a custom scheduling strategy.
 *
 * ### Multi-Core Support
 * For multi-core systems, the scheduler provides separate implementations for each core. The
 * CPU number is passed as a parameter to the scheduler functions to specify the target core.
 *
 * ### Error Handling
 * The scheduler functions use an error code parameter to report errors. The error codes are
 * defined in the STL error type enumeration (`STL_ERROR_T`).
 *
 * @note Weak definitions are provided for custom schedulers. Users must overwrite these
 *       definitions to implement their own logic.
 *
 * @pre Ensure that the STL configuration macros are properly defined in the configuration
 *      header files.
 *
 * @see stl_cfg.h
 * @see stl_scheduler.h
 * @see stl_types.h
 */
#if __STL__
#ifndef __STL_SCHEDULER__MODULE__
#define __STL_SCHEDULER__MODULE__
#include "stl_scheduler.h"
#include "stl_tssp.h"
#include "stl_cfg.h"
#include "stl_types.h"

#if (STL_BOOT_TEST == 0u)
/**
 * @brief This function is used to schedule the bootime tests
 * It is called by the main function to execute the bootime tests, sequentially.
 * It is used to schedule the bootime tests in a sequential manner for a given CPU (in case of multicore).
 *
 * @param cpu CPU number (not used in single core)
 * @param err Error code
 * @return None
 */
STATIC_KEYWORD void STL_scheduler_bootime(STL_CPUS cpu, STL_ERROR_T *err)
{
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

#if (STL_MULTICORE_SOC == 1u)
	STL_TSSP_CPU_swap_ivor(cpu);
#else
	STL_TSSP_CPU_swap_ivor();
#endif

	for (i = 0; i < STL_TOT_BT_ROUTINE; i++)
	{
		/* Set test configuration */
#if (STL_MULTICORE_SOC == 1u)
		STL_TSSP_set_test_config_bootime(cpu, i, err);
#else
		STL_TSSP_set_test_config_bootime(i, err);
#endif
		if (*err != STL_ERROR_NONE)
		{
#if (STL_MULTICORE_SOC == 1u)
			STL_TSSP_CPU_restore_ivor(cpu);
#else
			STL_TSSP_CPU_restore_ivor();
#endif
			return;
		}

		/* Execute test and update signature */
#if (STL_MULTICORE_SOC == 1u)
		signature = SBST_BT[cpu][i]();
		STL_em_update_sig(i, signature, cpu, err);
#else
		signature = SBST_BT[i]();
		STL_em_update_sig(i, signature, err);
#endif

		/* Restore test configuration */
#if (STL_MULTICORE_SOC == 1u)
		STL_TSSP_restore_test_config_bootime(cpu, i, err);
#else
		STL_TSSP_restore_test_config_bootime(i, err);
#endif

		/* Check for errors */
		if (*err != STL_ERROR_NONE)
		{
#if (STL_MULTICORE_SOC == 1u)
			STL_TSSP_CPU_restore_ivor(cpu);
#else
			STL_TSSP_CPU_restore_ivor();
#endif
			return;
		}
	}

#if (STL_MULTICORE_SOC == 1u)
	STL_TSSP_CPU_restore_ivor(cpu);
#else
	STL_TSSP_CPU_restore_ivor();
#endif
}
#endif /* STL_BOOT_TEST */
/**
 * @brief This function is used to schedule the runtime tests
 * It is called by the main function to execute the runtime tests.
 *
 * Note Scheduler type:
 *                       - 0 Sequential SBST scheduler (for runtime tests only)
 *                       - 1 Chunk-based SBST scheduler (for runtime tests only)
 *                       - 2 Custom (overwrite the definition)
 */

#if (STL_RUNTIME_TEST == 0u)

#if (STL_SCHEDULER_TYPE == 0u)
/**
 * @brief Sequential SBST scheduler for runtime tests
 *
 * This scheduler executes all runtime tests sequentially.
 *
 * @param err Error code
 * @return None
 */
STATIC_KEYWORD void STL_scheduler_runtime_singlecore(STL_ERROR_T *err)
{
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	for (i = 0; i < STL_TOT_RT_ROUTINE; i++)
	{
		signature = SBST_RT[i]();
		STL_em_update_sig(i, signature, err);

		if (*err != STL_ERROR_NONE)
		{
			return;
		}
	}
}

#elif (STL_SCHEDULER_TYPE == 1u)
/**
 * @brief Chunk-based SBST scheduler for runtime tests
 *
 * This scheduler executes runtime tests in chunks, allowing partial execution
 * of the test set in each scheduling cycle.
 *
 * @param err Error code
 * @return None
 */
STATIC_KEYWORD void STL_scheduler_runtime_singlecore(STL_ERROR_T *err)
{
	static STL_SIZE_T index = 0;
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	for (i = index; i < STL_RT_CHUNK && index < STL_TOT_RT_ROUTINE; i++, index++)
	{
		signature = SBST_RT[i]();
		STL_em_update_sig(i, signature, err);

		if (*err != STL_ERROR_NONE)
		{
			return;
		}
	}

	if (index >= STL_TOT_RT_ROUTINE)
	{
		index = 0; // Reset index after completing all tests
	}
}

#elif (STL_SCHEDULER_TYPE == 2u)
/**
 * @brief Custom SBST scheduler for runtime tests
 *
 * This scheduler allows custom implementation by the user.
 * The user must overwrite this function definition.
 *
 * @param err Error code
 * @return None
 */
WEAK_KEYWORD void STL_scheduler_runtime_singlecore(STL_ERROR_T *err)
{
	// Weak definition for custom implementation
	// The user must overwrite this function with their own logic.
	*err = STL_ERROR_CUSTOM_SCHEDULER_NOT_IMPLEMENTED;
}

#endif /* STL_SCHEDULER_TYPE */

#if (STL_MULTICORE_SOC == 1u)
#if (STL_SCHEDULER_TYPE == 0u)
/**
 * @brief Sequential SBST scheduler for runtime tests (multicore)
 *
 * This scheduler executes all runtime tests sequentially for a specific CPU.
 *
 * @param cpu CPU number
 * @param err Error code
 * @return None
 */
STATIC_KEYWORD void STL_scheduler_runtime_multicore(STL_CPUS cpu, STL_ERROR_T *err)
{
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	for (i = 0; i < STL_TOT_RT_ROUTINE; i++)
	{
		/* Set test configuration */
		STL_TSSP_set_test_config_runtime(cpu, i, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}

		/* Execute test and update signature */
		signature = SBST_RT[cpu][i]();
		STL_em_update_sig(i, signature, cpu, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}

		/* Restore test configuration */
		STL_TSSP_restore_test_config_runtime(cpu, i, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}
	}
}

#elif (STL_SCHEDULER_TYPE == 1u)
/**
 * @brief Chunk-based SBST scheduler for runtime tests (multicore)
 *
 * This scheduler executes runtime tests in chunks for a specific CPU, allowing
 * partial execution of the test set in each scheduling cycle.
 *
 * @param cpu CPU number
 * @param err Error code
 * @return None
 */
STATIC_KEYWORD void STL_scheduler_runtime_multicore(STL_CPUS cpu, STL_ERROR_T *err)
{
	static STL_SIZE_T index[STL_MULTICORE_SOC] = {0}; // Static index for each CPU
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	for (i = index[cpu]; i < STL_RT_CHUNK && index[cpu] < STL_TOT_RT_ROUTINE; i++, index[cpu]++)
	{
		/* Set test configuration */
		STL_TSSP_set_test_config_runtime(cpu, i, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}

		/* Execute test and update signature */
		signature = SBST_RT[cpu][i]();
		STL_em_update_sig(i, signature, cpu, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}

		/* Restore test configuration */
		STL_TSSP_restore_test_config_runtime(cpu, i, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}
	}

	if (index[cpu] >= STL_TOT_RT_ROUTINE)
	{
		index[cpu] = 0; // Reset index after completing all tests
	}
}

#elif (STL_SCHEDULER_TYPE == 2u)
/**
 * @brief Custom SBST scheduler for runtime tests (multicore)
 *
 * This scheduler allows custom implementation by the user for a specific CPU.
 * The user must overwrite this function definition.
 *
 * @param cpu CPU number
 * @param err Error code
 * @return None
 */
WEAK_KEYWORD void STL_scheduler_runtime_multicore(STL_CPUS cpu, STL_ERROR_T *err)
{
	// Weak definition for custom implementation
	// The user must overwrite this function with their own logic.
	*err = STL_ERROR_CUSTOM_SCHEDULER_NOT_IMPLEMENTED;
}

#endif /* STL_SCHEDULER_TYPE */

#endif /* STL_RUNTIME_TEST */
/**
 * @brief This function schedules runtime tests.
 * It determines whether to use single-core or multi-core scheduling based on the configuration.
 *
 * @param cpu CPU number (used only in multi-core configurations)
 * @param err Pointer to an error code variable
 * @return None
 */
void STL_schedule_runtime(STL_CPUS cpu, STL_ERROR_T *err)
{
	static STL_SIZE_T index = 0; // Static index for chunk-based scheduling
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	// Initialize error code to no error
	*err = STL_ERROR_NONE;

#if STL_RUNTIME_TEST == 0
	// If runtime tests are disabled, set error and return
	*err = STL_NO_RT_ROUTINE;
	return;
#else

#if (STL_MULTICORE_SOC == 1u)
	// Multi-core configuration
	if (cpu > STL_MULTICORE_SOC)
	{
		// Check if the CPU number is out of bounds
		*err = STL_CPU_OUT_OF_BOUNDS;
		return;
	}
	// Call the multi-core runtime scheduler
	STL_scheduler_runtime_multicore(cpu, err);
#else
	// Single-core configuration
	(void)cpu; // Suppress unused parameter warning
	STL_scheduler_runtime_singlecore(err);
#endif /* STL_MULTICORE_SOC */

#endif /* STL_RUNTIME_TEST */
}

/**
 * @brief This function schedules boot-time tests.
 * It determines whether to use single-core or multi-core scheduling based on the configuration.
 *
 * @param cpu CPU number (used only in multi-core configurations)
 * @param err Pointer to an error code variable
 * @return None
 */
void STL_schedule_bootime(STL_CPUS cpu, STL_ERROR_T *err)
{
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;

	// Initialize error code to no error
	*err = STL_ERROR_NONE;

#if (STL_BOOT_TEST == 0u)
	// If boot-time tests are disabled, set error and return
	*err = STL_NO_BT_ROUTINE;
	return;
#else

#if (STL_MULTICORE_SOC == 1u)
	// Multi-core configuration
	if (cpu > STL_MULTICORE_SOC)
	{
		// Check if the CPU number is out of bounds
		*err = STL_CPU_OUT_OF_BOUNDS;
		return;
	}
	// Call the multi-core boot-time scheduler
	STL_scheduler_bootime_multicore(cpu, err);
#else
	// Single-core configuration
	(void)cpu; // Suppress unused parameter warning
	STL_scheduler_bootime(err);
#endif /* STL_MULTICORE_SOC */

#endif /* STL_BOOT_TEST */
}

#endif /*__STL_SCHEDULER_MODULE__*/
#endif /*__STL__*/