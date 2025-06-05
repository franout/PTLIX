#if __STL__
#ifndef __STL_EM__MODULE__
#define __STL_EM__MODULE__
#include "stl_cfg.h"

#if STL_ERROR_MANAGEMENT_ENABLED
/*
 * static internal structure for signature and error collection
 *
 * */



#include "stl.h"

#include "stl_al_os.h"
#include "stl_tssp.h"
#include "stl_core.h"


#ifdef __cplusplus
/**
 * @file stl_error_management.h
 * @brief Header file for error management in STL (Self-Test Library).
 *
 * This file provides the declarations for error handling functions and data structures
 * used in the STL framework. It includes functions for initializing error handling,
 * managing runtime and boot-time errors, and retrieving error signatures.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @struct STL_EM_TEST_T
 * @brief Structure representing a test for error management.
 *
 * @var STL_EM_TEST_T::sig
 * Signature of the test.
 * @var STL_EM_TEST_T::mismatch
 * Boolean indicating if there is a mismatch.
 */

/**
 * @brief Initializes the error management system.
 *
 * @param err Pointer to the error structure to initialize.
 */
void STL_em_init(STL_ERROR_T *err);

/**
 * @brief Handles a runtime failure for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param err Pointer to the error structure to update.
 * @return The size of the runtime failure data.
 */
STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu, STL_ERROR_T *err);

/**
 * @brief Handles all runtime failures for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param vect Pointer to the vector of failed tests.
 * @param err Pointer to the error structure to update.
 */
void STL_em_failed_runtime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err);

/**
 * @brief Handles all boot-time failures for a specific CPU.
 *
 * @param cpu The CPU identifier.
 * @param vect Pointer to the vector of failed tests.
 * @param err Pointer to the error structure to update.
 */
void STL_em_failed_bootime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect, STL_ERROR_T *err);

/**
 * @brief Retrieves the boot-time signature for a specific CPU and index.
 *
 * @param cpu The CPU identifier.
 * @param index The index of the signature to retrieve.
 * @param err Pointer to the error structure to update.
 * @return The boot-time signature.
 */
STL_SIGNATURE_T STL_em_bt_get_signature(STL_CPUS cpu, STL_SIZE_T index, STL_ERROR_T *err);

/**
 * @brief Retrieves the runtime signature for a specific CPU and index.
 *
 * @param cpu The CPU identifier.
 * @param index The index of the signature to retrieve.
 * @param err Pointer to the error structure to update.
 * @return The runtime signature.
 */
STL_SIGNATURE_T STL_em_rt_get_signature(STL_CPUS cpu, STL_SIZE_T index, STL_ERROR_T *err);

#ifdef __cplusplus
}
#endif /* __cplusplus */