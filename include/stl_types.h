#ifndef __STL_TYPES_H__
#define __STL_TYPES_H__

/**
 * @file stl_types.h
 * @brief This header file defines common types, constants, and error codes used in the STL (Self-Test Library).
 *
 * It includes definitions for boolean values, null pointers, error codes, and various type aliases
 * used throughout the STL. Additionally, it provides type definitions for function pointers and
 * CPU identifiers in multicore systems.
 */

/**
 * @def STL_TRUE
 * @brief Macro representing a boolean true value.
 */

/**
 * @def STL_FALSE
 * @brief Macro representing a boolean false value.
 */

/**
 * @def STL_NULL
 * @brief Macro representing a null pointer value.
 */

/**
 * @typedef STL_SIGNATURE_T
 * @brief Type used for signature values in STL operations.
 */

/**
 * @enum STL_ERROR_T
 * @brief Enumeration of error codes for STL operations.
 *
 * This enumeration defines various error codes that can be returned by STL functions.
 * Each error code corresponds to a specific type of error encountered during operation.
 *
 * @var STL_ERROR_T::STL_ERROR_NONE
 * No error occurred.
 *
 * @var STL_ERROR_T::STL_ERROR_NOT_IMPLEMENTED
 * The requested feature is not implemented.
 *
 * @var STL_ERROR_T::STL_ERROR_TASK_ALLOCATION
 * Error occurred during task allocation.
 *
 * @var STL_ERROR_T::STL_ERROR_RELOCATION
 * Error occurred during relocation.
 *
 * @var STL_ERROR_T::STL_ERROR_SIG_MISMATCH
 * Signature mismatch error.
 *
 * @var STL_ERROR_T::STL_ERROR_INDEX
 * Index error.
 *
 * @var STL_ERROR_T::STL_ERROR_SBST
 * Subsystem error.
 *
 * @var STL_ERROR_T::STL_CPU_OUT_OF_BOUNDS
 * CPU index is out of bounds.
 *
 * @var STL_ERROR_T::STL_INDEX_OUT_OF_BOUNDS
 * Index is out of bounds.
 *
 * @var STL_ERROR_T::STL_NO_RT_ROUTINE
 * No runtime routine is available.
 *
 * @var STL_ERROR_T::STL_NO_BT_ROUTINE
 * No boot-time routine is available.
 *
 * @var STL_ERROR_T::STL_ERROR_CUSTOM_SCHEDULER_NOT_IMPLEMENTED
 * Custom scheduler is not implemented.
 */

/**
 * @typedef STL_BOOL
 * @brief Boolean type used in STL operations.
 */

/**
 * @typedef STL_SIZE_T
 * @brief Type used to represent sizes in STL operations.
 */

/**
 * @typedef STL_INT32U_T
 * @brief Unsigned 32-bit integer type used in STL operations.
 */

/**
 * @typedef STL_ADDR_T
 * @brief Type used to represent addresses in STL operations.
 */

/**
 * @typedef STL_CPUS
 * @brief Type used to define the CPU number in a multicore system.
 *
 * This type is used to identify the CPU on which the test is running. It is utilized
 * in the STL_schedule_runtime and STL_schedule_bootime functions.
 */

/**
 * @typedef STL_FUNCT_PTR_T
 * @brief Function pointer type for STL functions.
 *
 * This type represents a pointer to a function that returns an STL_SIGNATURE_T value.
 */
#if defined(__GNUC__) || defined(__ICCARM__) || defined(__CC_ARM) || defined(__ARMCC_VERSION) 
#include "stdint.h" // For fixed-width integer types
#include "stddef.h" // For size_t type
#else
#include "typedefs.h"
#endif /* __GNUC__ */

// Boolean definitions
#define STL_TRUE 1u
#define STL_FALSE 0u

// Null pointer definition
#define STL_NULL 0x00000000UL

// Type for signature values
typedef int STL_SIGNATURE_T;

// Error codes for STL operations
typedef enum
{
	STL_ERROR_NONE = 0,				// No error
	STL_ERROR_NOT_IMPLEMENTED = 2,	// Feature not implemented
	STL_ERROR_TASK_ALLOCATION = 10, // Task allocation error

	STL_ERROR_RELOCATION = 20, // Relocation error

	STL_ERROR_SIG_MISMATCH = 30, // Signature mismatch error

	STL_ERROR_INDEX = 40, // Index error

	STL_ERROR_SBST = 50, // Subsystem error

	STL_CPU_OUT_OF_BOUNDS = 60,	  // CPU index out of bounds
	STL_INDEX_OUT_OF_BOUNDS = 70, // Index out of bounds

	STL_NO_RT_ROUTINE = 80, // No runtime routine available
	STL_NO_BT_ROUTINE = 90, // No boot-time routine available

	STL_ERROR_CUSTOM_SCHEDULER_NOT_IMPLEMENTED = 100 // Custom scheduler not implemented
} STL_ERROR_T;

// Boolean type
typedef char STL_BOOL;

// Size type for STL operations
typedef uint16_t STL_SIZE_T;

// Unsigned 32-bit integer type
typedef uint32_t STL_INT32U_T;

// Address type
typedef uint32_t STL_ADDR_T;

/**
 * @brief STL_CPUS is used to define the CPU number in a multicore system.
 * It is used to identify the CPU on which the test is running.
 * This is utilized in the STL_schedule_runtime and STL_schedule_bootime functions.
 */
typedef uint8_t STL_CPUS;

// Function pointer type for STL functions
typedef STL_SIGNATURE_T (*STL_FUNCT_PTR_T)(void);

#endif /* __STL_TYPES_H__ */
