/**
 * @file stl_scheduler.h
 * @brief Header file for the STL scheduler module.
 *
 * This file contains the declarations for the STL scheduler functions, which
 * are used to schedule boot-time and runtime tests in a sequential manner.
 * The scheduler supports both single-core and multi-core CPUs.
 *
 * @details
 * - STL_scheduler_bootime: Schedules and executes boot-time tests.
 * - STL_scheduler_runtime: Schedules and executes runtime tests.
 *
 * @note The functions are conditionally compiled based on STL_BOOT_TEST and
 * STL_RUNTIME_TEST macros.
 *
 * @author Francesco Angione (franout)
 * @date 2023-10-03
 */
#if __STL__
#ifndef __STL_SCHEDULER_H__
#define __STL_SCHEDULER_H__

#include "stl.h"

#include "stl_al_os.h"
#include "stl_core.h"
#include "stl_tssp.h"

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/

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
void STL_scheduler_bootime(STL_CPUS cpu, STL_ERROR_T *err);
#endif /*STL_BOOT_TEST*/
#if (STL_RUNTIME_TEST == 0u)
/**
 * @brief This function is used to schedule the runtime tests
 * It is called by the main function to execute the runtime tests, sequentially.
 * It is used to schedule the runtime tests in a sequential manner for a given CPU (in case of multicore).
 *
 * @param cpu CPU number (not used in single core)
 * @param err Error code
 * @return None
 */
void STL_scheduler_runtime(STL_CPUS cpu, STL_ERROR_T *err);
#endif /*STL_RUNTIME_TEST*/

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*__STL_SCHEDULER_H__*/
#endif /*__STL__*/