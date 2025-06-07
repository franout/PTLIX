#if __STL__
#ifndef __STL_AL_CPU_H__
#define __STL_AL_CPU_H__

/**
 * @file stl_al_cpu.h
 * @brief CPU services for the Test Setup Support Package (TSSP).
 * This file provides functions for CPU-specific operations such as restoring and swapping the interrupt vector table,
 * configuring the Memory Protection Unit (MPU), and managing CPU-specific configurations.
 *
 * @note This file is part of the Test Setup Support Package (TSSP) and is intended for use in embedded systems.
 * It is designed to be included in the TSSP implementation files.
 */

/**
 * STL_NUM_CPU
 * @brief Number of CPUs in the system.
 * This macro defines the number of CPUs available in the system.
 * It is used to determine the number of CPU-specific configurations and operations that can be performed.
 * The value is set to 2 for systems with two CPUs.
 * @note This value may need to be adjusted based on the actual number of CPUs in the system.
 * @see STL_CPU_MPU_CFG_t for Memory Protection Unit configuration.
 * @see STL_TSSP_CPU_configure_mpu for configuring the MPU.
 * @see STL_TSSP_CPU_restore_ivor for restoring the interrupt vector table.
 */
#define STL_NUM_CPU 2u

#endif /*__STL_AL_CPU_H__*/
#endif /*__STL__*/