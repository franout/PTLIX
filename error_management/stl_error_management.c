#if __STL__
#ifndef __STL_EM__MODULE__
#define __STL_EM__MODULE__
#include "stl_cfg.h"

#if STL_ERROR_MANAGEMENT_ENABLED

#include "stl_cfg.h"
#include "stl_error_management.h"
#include "stl_types.h"

/**
 * @file stl_error_management.c
 * @brief This file contains the implementation of error management structures and variables
 *        for the STL (Self-Test Library) framework.
 *
 * The code defines structures and variables used for tracking error signatures and failed tests
 * in both single-core and multi-core execution environments.
 */

/**
 * @typedef STL_EM_TEST_T
 * @brief Structure to hold error management test data.
 *
 * This structure contains the signature and mismatch status for error management tests.
 *
 * @var STL_EM_TEST_T::sig
 * Signature of the test for error management.
 *
 * @var STL_EM_TEST_T::mismatch
 * Boolean flag indicating if there is a mismatch in the test.
 */

/**
 * @def STL_MULTICORE_EXECUTION
 * @brief Macro to enable or disable multi-core execution support.
 *
 * When defined, the code supports multi-core execution by maintaining separate
 * error management data for each CPU core.
 */

/**
 * @var em_bt_sign
 * @brief Array to store error management test data for background tests (BT).
 *
 * In multi-core execution mode, this array is indexed by both routine and CPU core.
 * In single-core execution mode, it is indexed only by routine.
 */

/**
 * @var em_rt_sign
 * @brief Array to store error management test data for runtime tests (RT).
 *
 * In multi-core execution mode, this array is indexed by both routine and CPU core.
 * In single-core execution mode, it is indexed only by routine.
 */

/**
 * @var last_failed
 * @brief Variable to store the last failed test information.
 *
 * In multi-core execution mode, this is an array indexed by CPU core.
 * In single-core execution mode, it is a single variable.
 *
 * @note This variable is declared as `volatile` to ensure proper synchronization
 *       in multi-threaded or interrupt-driven environments.
 */
typedef struct
{
	STL_SIGNATURE_T sig;
	STL_BOOL mismatch;
} STL_EM_TEST_T;

#if STL_MULTICORE_EXECUTION
static STL_EM_TEST_T em_bt_sign[STL_NUM_CPU][STL_TOT_BT_ROUTINE];
static STL_EM_TEST_T em_rt_sign[STL_NUM_CPU][STL_TOT_RT_ROUTINE];
#else
static STL_EM_TEST_T em_bt_sign[STL_TOT_BT_ROUTINE];
static STL_EM_TEST_T em_rt_sign[STL_TOT_RT_ROUTINE];
#endif /*STL_MULTICORE_EXECUTION*/

#if STL_MULTICORE_EXECUTION
volatile static STL_FAILED_TEST_T last_failed[STL_NUM_CPU];
#else
volatile static STL_FAILED_TEST_T last_failed;
#endif /*STL_MULTICORE_EXECUTION*/

/**
 * @brief Initializes the error management system.
 *
 * This function initializes the error management system by setting up the
 * error management test data structures and resetting the last failed test
 * information. It is called at the beginning of the program to prepare for
 * error management operations.
 *
 * @param err Pointer to an STL_ERROR_T variable where the error status will be updated.
 *            It is set to STL_ERROR_NONE if no errors occur.
 */
void STL_em_init(STL_ERROR_T *err)
{
	*err = STL_ERROR_NONE;
#if STL_ERROR_MANAGEMENT_ENABLED
	STL_SIZE_T i, j;

#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_NUM_CPU; j++)
	{
		last_failed[j] = {0};
		for (i = 0; i < STL_BOOTTIME_ROUTINES; i++)
		{
			em_bt_sign[j][i].sig = 0;
			em_bt_sign[j][i].mismatch = STL_FALSE;
		}

		for (i = 0; i < STL_RUNTIME_ROUTINES; i++)
		{
			em_rt_sign[j][i].sig = 0;
			em_rt_sign[j][i].mismatch = STL_FALSE;
		}
	}
#else
	last_failed = {0};
	for (i = 0; i < STL_TOT_BT_ROUTINE; i++)
	{
		em_bt_sign[i].sig = 0;
		em_bt_sign[i].mismatch = STL_FALSE;
	}

	for (i = 0; i < STL_TOT_RT_ROUTINE; i++)
	{
		em_rt_sign[i].sig = 0;
		em_rt_sign[i].mismatch = STL_FALSE;
	}
#endif /* STL_MULTICORE_EXECUTION*/

#endif /*STL_ERROR_MANAGEMENT_ENABLED*/
}

/**
 * @brief Retrieves the last failed test information for a specific CPU.
 *
 * This function retrieves the last failed test information for a given CPU.
 * It checks if the CPU identifier is within valid bounds and returns the
 * corresponding failed test information. If the CPU identifier is out of bounds,
 * an error code is set in the provided error pointer.
 *
 * @param cpu The CPU identifier (used in multi-core execution mode).
 * @param vect Pointer to an STL_FAILED_TEST_T structure where the failed test
 *             information will be stored.
 * @param err Pointer to an STL_ERROR_T variable where the error status will be updated.
 *            It is set to STL_CPU_OUT_OF_BOUNDS if the CPU identifier is invalid
void STL_em_get_last_failed(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err)
{
#if STL_MULTICORE_EXECUTION
	if (cpu < 0 || cpu > STL_NUM_CPU)
	{
		*err = STL_CPU_OUT_OF_BOUNDS;
		return;
	}
	*vect = last_failed[cpu];
#else
	*vect = last_failed;
#endif /*STL_MULTICORE_EXECUTION*/
*err = STL_ERROR_NONE;
return;
}

/**
 * @brief Checks for failed runtime tests and returns the index of the first failure.
 *
 * This function iterates through the runtime test signatures and checks for
 * any mismatches. If a mismatch is found, it returns the index of the failed test.
 * In multi-core execution mode, it checks all CPUs for mismatches.
 *
 * @param cpu The CPU identifier (used in multi-core execution mode).
 * @param err Pointer to an STL_ERROR_T variable where the error status will be updated.
 *            It is set to STL_ERROR_NONE if no errors occur.
 *
 * @return The index of the first failed runtime test, or -1 if no failures are found.
 */
STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu, STL_ERROR_T *err)
{
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++)
	{
		if (em_rt_sign[cpu][j].mismatch == STL_TRUE)
		{
			return j;
		}
	}
#else
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++)
	{
		if (em_rt_sign[j].mismatch == STL_TRUE)
		{
			return j;
		}
	}
#endif /*STL_MULTICORE_EXECUTION*/
	return -1;
}
/**
 * @brief Checks for failed boot-time tests and returns the index of the first failure.
 *
 * This function iterates through the boot-time test signatures and checks for
 * any mismatches. If a mismatch is found, it returns the index of the failed test.
 * In multi-core execution mode, it checks all CPUs for mismatches.
 *
 * @param cpu The CPU identifier (used in multi-core execution mode).
 * @param err Pointer to an STL_ERROR_T variable where the error status will be updated.
 *            It is set to STL_ERROR_NONE if no errors occur.
 *
 * @return The index of the first failed boot-time test, or -1 if no failures are found.
 */
STL_SIZE_T STL_em_bootitme_failed(STL_CPUS cpu, STL_ERROR_T *err)
{
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	/*cause the master core will wait for booting the OS*/
	for (i = 0; i < STL_NUM_CPU; i++)
	{
		for (j = 0; j < STL_TOT_BT_ROUTINE; j++)
		{
			if (em_bt_sign[i][j].mismatch == STL_TRUE)
			{
				return j;
			}
		}
	}
#else
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++)
	{
		if (em_bt_sign[j].mismatch == STL_TRUE)
		{
			return j;
		}
	}
#endif /*STL_MULTICORE_EXECUTION*/
	return -1;
}
/**
 * @brief Handles the failed runtime tests and updates the error vector.
 *
 * This function checks for mismatches in the runtime signatures and updates
 * the provided error vector with the index and signature of the failed tests.
 * It supports both single-core and multi-core execution environments.
 *
 * @param[in] cpu The CPU identifier (used in multi-core execution mode).
 * @param[out] vect Pointer to an array of STL_FAILED_TEST_T structures where
 *                  the failed test information will be stored.
 * @param[out] err Pointer to an STL_ERROR_T variable where the error status
 *                 will be updated. It is set to STL_ERROR_NONE if no errors occur.
 *
 * @note The behavior of this function depends on whether STL_MULTICORE_EXECUTION
 *       is defined. In multi-core mode, the function processes the runtime
 *       signatures for the specified CPU. In single-core mode, it processes
 *       the signatures for all routines.
 */
void STL_em_failed_runtime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err)
{
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;
#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++)
	{
		if (em_rt_sign[cpu][j].mismatch == STL_TRUE)
		{
			vect[j].index = j;
			vect[j].signature = em_rt_sign[cpu][j].sig;
		}
	}
#else
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++)
	{
		if (em_rt_sign[j].mismatch == STL_TRUE)
		{
			vect[j].index = j;
			vect[j].signature = em_rt_sign[j].sig;
		}
	}
#endif /*STL_MULTICORE_EXECUTION*/
}

/**
 * @brief Handles the failed boot-time tests and updates the error vector.
 *
 * This function checks for mismatches in the boot-time signatures and updates
 * the provided error vector with the index and signature of the failed tests.
 * It supports both single-core and multi-core execution environments.
 *
 * @param[in] cpu The CPU identifier (used in multi-core execution mode).
 * @param[out] vect Pointer to an array of STL_FAILED_TEST_T structures where
 *                  the failed test information will be stored.
 * @param[out] err Pointer to an STL_ERROR_T variable where the error status
 *                 will be updated. It is set to STL_ERROR_NONE if no errors occur.
 *
 * @note The behavior of this function depends on whether STL_MULTICORE_EXECUTION
 *       is defined. In multi-core mode, the function processes the boot-time
 *       signatures for the specified CPU. In single-core mode, it processes
 *       the signatures for all routines.
 */
}
void STL_em_failed_bootime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err)
{
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;
#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++)
	{
		if (em_bt_sign[cpu][j].mismatch == STL_TRUE)
		{
			vect[j].index = j;
			vect[j].signature = em_bt_sign[cpu][j].sig;
		}
	}
#else
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++)
	{
		if (em_bt_sign[j].mismatch == STL_TRUE)
		{
			vect[j].index = j;
			vect[j].signature = em_bt_sign[j].sig;
		}
	}
#endif /*STL_MULTICORE_EXECUTION*/
}
/**
 * @brief Retrieves the signature of a backtrace routine for a given CPU and index.
 *
 * This function fetches the signature of a backtrace routine based on the specified
 * CPU and index. It performs boundary checks to ensure the CPU and index values
 * are within valid ranges. If the values are out of bounds, an appropriate error
 * code is set in the provided error pointer.
 *
 * @param[in] cpu The CPU identifier (only relevant if STL_MULTICORE_EXECUTION is enabled).
 * @param[in] index The index of the backtrace routine.
 * @param[out] err Pointer to an STL_ERROR_T variable where the error code will be stored.
 *                 Possible error codes:
 *                 - STL_CPU_OUT_OF_BOUNDS: The CPU identifier is out of bounds.
 *                 - STL_INDEX_OUT_OF_BOUNDS: The index is out of bounds.
 *                 - STL_ERROR_NONE: No error occurred.
 *
 * @return The signature of the backtrace routine. Returns 0 if an error occurs.
 *
 * @note If STL_MULTICORE_EXECUTION is enabled, the function checks the CPU identifier
 *       and retrieves the signature from a multi-dimensional array. Otherwise, it
 *       retrieves the signature from a single-dimensional array.
 */
STL_SIGNATURE_T STL_em_rt_get_signature(STL_CPUS cpu, STL_SIZE_T index, STL_ERROR_T *err)
{
#if STL_MULTICORE_EXECUTION
	if (cpu < 0 || cpu > STL_NUM_CPU)
	{
		*err = STL_CPU_OUT_OF_BOUNDS;
		return 0;
	}
#endif /*STL_MULTICORE_EXECUTION*/
	if (index < 0 || index > STL_TOT_RT_ROUTINE)
	{
		*err = STL_INDEX_OUT_OF_BOUNDS;
		return 0;
	}
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	return em_rt[cpu][index].sig;
#else
	return em_rt_sign[index].sig;
#endif /*STL_MULTICORE_EXECUTION*/
}

#endif /*STL_ERROR_MANAGEMENT_ENABLED*/

#endif /*__STL_EM__MODULE__*/
#endif /*__STL__*/
