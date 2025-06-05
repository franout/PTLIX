#if 1 __STL__
#ifndef __STL_TSSP_H__
#define __STL_TSSP_H__

#include "stl_cfg.h"
#include "stl_types.h"

#if __cplusplus
extern "C"
/**
 * @file stl_tssp.h
 * @brief Test Setup Support Package (TSSP) header.
 *
 * This header file provides prototypes for the Test Setup Support Package functions,
 * which include CPU services, CSP/BSP services, and OS services. The functions are used
 * for configuring CPU-specific features (like IVOR handling and MPU configuration),
 * managing watchdog timers, setting and restoring test configurations, and creating/deleting
 * OS tasks for testing.
 *
 * The functionality is conditionally compiled based on configuration macros such as:
 * - STL_USE_MPU
 * - STL_USE_WATCHDOG
 * - STL_USE_FINE_GRAINED_WATCHDOG
 * - STL_MULTICORE_SOC
 * - STL_OS_PRESENT
 *
 * @note Ensure that the appropriate configuration macros are defined before including this header.
 *
 * @defgroup TSSP Test Setup Support Package
 * @{
 */

/*===========================================================================
 *                            CPU Services
 *===========================================================================*/
/**
 * @brief Restores the CPU IVOR (Initial Vector Offset Register) configuration.
 *
 * Use this function after swapping the IVOR registers to reinstate the default settings.
 */

/**
 * @brief Swaps the current CPU IVOR configuration.
 *
 * This function exchanges the current IVOR setup with an alternate configuration necessary
 * for certain test scenarios.
 */

/**
 * @brief Enumeration of MPU access permissions.
 *
 * These constants define the possible access permissions for a memory region configured in the MPU.
 * - STL_CPU_MPU_ACCESS_NONE: No permissions.
 * - STL_CPU_MPU_ACCESS_READ: Read-only permission.
 * - STL_CPU_MPU_ACCESS_WRITE: Write-only permission.
 * - STL_CPU_MPU_ACCESS_EXECUTE: Execute-only permission.
 * - STL_CPU_MPU_ACCESS_ALL: Full access (read, write, execute).
 */

/**
 * @brief Structure for MPU region configuration.
 *
 * This structure defines the properties of a memory region in the MPU including:
 * - Base address.
 * - Size of the region.
 * - Access permissions (of type STL_CPU_MPU_ACCESS_t).
 */

/**
 * @brief Configures the Memory Protection Unit (MPU).
 *
 * Sets up the MPU region using the provided configuration structure.
 *
 * @param mpu_cfg Pointer to the MPU configuration structure.
 */

/*===========================================================================
 *                          CSP/BSP Services
 *===========================================================================*/
/**
 * @brief Initializes the watchdog timer.
 *
 * For fine-grained configurations, initialize with explicit timeout and reset values.
 * Otherwise, initialize with default settings.
 *
 * @param timeout_value (Only when STL_USE_FINE_GRAINED_WATCHDOG is set) Timeout period for the watchdog.
 * @param reset_value (Only when STL_USE_FINE_GRAINED_WATCHDOG is set) Reset duration or parameters for the watchdog.
 */

/**
 * @brief Starts the watchdog timer.
 *
 * Begins the countdown of the watchdog timer to monitor system activity.
 */

/**
 * @brief Stops the watchdog timer.
 *
 * Halts the watchdog timer to prevent system resets during test execution.
 */

/**
 * @brief Resets the watchdog timer.
 *
 * Resets or "kicks" the watchdog timer to avoid an unintended system reset.
 */

/*===========================================================================
 *                        Test Configuration Services
 *===========================================================================*/
/**
 * @brief Sets the test configuration at boot time.
 *
 * Configures necessary parameters for a test before the test execution begins.
 * For multicore systems, the CPU identifier is passed as an argument.
 *
 * @param cpu (Optional, for multicore systems) The target CPU for which the test configuration applies.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 */

/**
 * @brief Restores the test configuration set at boot time.
 *
 * Reverts the boot time test configuration to its original state.
 *
 * @param cpu (Optional, for multicore systems) The target CPU whose configuration is restored.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 */

/**
 * @brief Sets the test configuration during runtime.
 *
 * Dynamically applies the test configuration parameters while the system is running.
 *
 * @param cpu (Optional, for multicore systems) The target CPU for the runtime configuration.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 */

/**
 * @brief Restores the runtime test configuration.
 *
 * Reverts any runtime test configuration modifications.
 *
 * @param cpu (Optional, for multicore systems) The target CPU whose runtime configuration is restored.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 */

/*===========================================================================
 *                             OS Services
 *===========================================================================*/
/**
 * @brief Creates an operating system task for test support.
 *
 * This function creates an OS task intended to manage test operations.
 * It is only available when OS support is enabled.
 */

/**
 * @brief Deletes an operating system task.
 *
 * Terminates and cleans up the OS task associated with test support.
 * It is only available when OS support is enabled.
 */

/** @} */
{
#endif /*__cplusplus*/

	/*****************************************************************************************************/
	/****************                    Test Setup Support Package                       ****************/
	/****************                          CPU services                               ****************/
	/*****************************************************************************************************/

	/**
	 * @brief Restore the CPU IVOR (Initial Vector Offset Register) configuration.
	 * This function is typically used to restore the interrupt vector table
	 * or save the current state of the interrupt vector table.
	 * The actual implementation will depend on the specific CPU architecture.
	 * @return void
	 * @note This function may involve low-level operations
	 * to manipulate the CPU's interrupt vector table.
	 * @warning This function should be used with caution, as improper use
	 * may lead to system instability.
	 */
	void STL_TSSP_CPU_restore_ivor(void);

	/**
	 * @brief Swap the current CPU IVOR configuration.
	 * This function is typically used to swap the interrupt vector table
	 * or restore the previous state of the interrupt vector table.
	 * The actual implementation will depend on the specific CPU architecture.
	 * @return void
	 * @note This function may involve low-level operations
	 * to manipulate the CPU's interrupt vector table.
	 * @warning This function should be used with caution, as improper use
	 * may lead to system instability.
	 */
	void STL_TSSP_CPU_swap_ivor(void);

#if (STL_USE_MPU > 0u)
	typedef enum
	{
		STL_CPU_MPU_ACCESS_NONE = 0u,	 /* No access permissions */
		STL_CPU_MPU_ACCESS_READ = 1u,	 /* Read access permission */
		STL_CPU_MPU_ACCESS_WRITE = 2u,	 /* Write access permission */
		STL_CPU_MPU_ACCESS_EXECUTE = 4u, /* Execute access permission */
		STL_CPU_MPU_ACCESS_ALL = 7u		 /* All access permissions (read, write, execute) */
	} STL_CPU_MPU_ACCESS_t;

	typedef struct
	{
		uint32_t base_address;		 /* Base address of the region */
		uint32_t size;				 /* Size of the region */
		STL_CPU_MPU_ACCESS_t access; /* Access permissions for the region */
	} STL_CPU_MPU_CFG_t;

	/**
	 * @brief Configure the Memory Protection Unit (MPU).
	 * This function is typically used to set up the MPU with the specified configuration parameters.
	 * @param mpu_cfg Pointer to the MPU configuration structure.
	 * @note The MPU configuration structure should contain the base address,
	 * size, and access permissions for the memory region.
	 * The actual implementation will depend on the specific CPU architecture.
	 * @return void
	 * @note Ensure that the mpu_cfg pointer is not NULL before accessing its members.
	 * @warning This function should be used with caution, as improper configuration
	 * of the MPU may lead to memory access violations or system instability.
	 */
	void STL_TSSP_CPU_configure_mpu(STL_CPU_MPU_CFG_t *mpu_cfg);
#endif /*STL_USE_MPU*/

	/*****************************************************************************************************/
	/****************                    Test Setup Support Package                       ****************/
	/****************                       CSP/BSP services                              ****************/
	/*****************************************************************************************************/

#if (STL_USE_WATCHDOG > 0u)

#if (STL_USE_FINE_GRAINED_WATCHDOG > 0u)
	/**
	 * @brief Initialize the watchdog timer with specific timeout and reset values.
	 * This function is typically used to set up the watchdog timer
	 * with the specified timeout and reset values.
	 *
	 */
	void STL_TSSP_CSP_watchdog_init(int32_t timeout_value, int32_t reset_value);
#else
	/**
	 * @brief Initialize the watchdog timer with default settings.
	 * This function is typically used to set up the watchdog timer
	 * with default settings.
	 * It is used when fine-grained watchdog configuration is not required.
	 */
	void STL_TSSP_CSP_watchdog_init(void);
#endif /*STL_USE_FINE_GRAINED_WATCHDOG*/
	   /**
		* @brief Start the watchdog timer.
		* This function is typically used to begin the countdown of the watchdog timer
		* to monitor system activity.
		* It is used to ensure that the system remains responsive and does not hang.
		*/
	void STL_TSSP_CSP_watchdog_start(void);
	/**
	 * @brief Stop the watchdog timer.
	 * This function is typically used to halt the watchdog timer
	 * to prevent system resets during test execution.
	 * It is used to ensure that the system can complete its operations without being interrupted by the watchdog.
	 * @note This function should be used with caution, as stopping the watchdog timer
	 * may lead to system instability if the system hangs or becomes unresponsive.
	 */
	void STL_TSSP_CSP_watchdog_stop(void);
	/**
	 * @brief Reset the watchdog timer.
	 * This function is typically used to reset the watchdog timer
	 * to prevent system resets during test execution.
	 * It is used to ensure that the system can complete its operations without being interrupted by the watchdog.
	 * @note This function should be used with caution, as resetting the watchdog timer
	 * may lead to system instability if the system hangs or becomes unresponsive.
	 */
	void STL_TSSP_CSP_watchdog_reset(void);
#endif /*STL_USE_WATCHDOG*/

/**
 * Test configuration specific function
 */
#if (STL_MULTICORE_SOC > 0u)
    /**
     * @brief Pointer type for test setup support package setup functions.
     * This type is used to define pointers to functions that set up test configurations
     * for the Test Setup Support Package (TSSP).
     * It is typically used in multicore systems where each CPU may have its own configuration.
     * @note This type is defined to facilitate the use of function pointers for test setup functions.
     * @see STL_TSSP_set_test_config_bootime, STL_TSSP_restore_test_config_bootime,
     *     STL_TSSP_set_test_config_runtime, STL_TSSP_restore_test_config_runtime
     * @warning Ensure that the function pointers are correctly assigned
     * before using them, as incorrect assignments may lead to undefined behavior.
     */
    typedef void (*STL_TSSP_TEST_SETUP_PTR_T)(void);

    /**
     * @brief Pointer type for test setup support package restore functions.
     * This type is used to define pointers to functions that restore test configurations
     * for the Test Setup Support Package (TSSP).
     * It is typically used in multicore systems where each CPU may have its own configuration.
     * @note This type is defined to facilitate the use of function pointers for restoring test configurations.
     * @see STL_TSSP_set_test_config_bootime, STL_TSSP_restore_test_config_bootime,
     *     STL_TSSP_set_test_config_runtime, STL_TSSP_restore_test_config_runtime
     * @warning Ensure that the function pointers are correctly assigned
     * before using them, as incorrect assignments may lead to undefined behavior. 
     */
    typedef void (*STL_TSSP_TEST_RESTORE_PTR_T)(void);

	/** * @brief Set the test configuration at boot time for a specific CPU.
	 * This function configures necessary parameters for a test before the test execution begins.
	 * It is used in multicore systems where each CPU may have its own configuration.
	 */
	void STL_TSSP_set_test_config_bootime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T *);
	/**
	 * @brief Restore the test configuration set at boot time for a specific CPU.
	 * This function reverts the boot time test configuration to its original state.
	 * It is used in multicore systems where each CPU may have its own configuration.
	 *
	 */
	void STL_TSSP_restore_test_config_bootime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T *);
	/**
	 * @brief Set the test configuration during runtime for a specific CPU.
	 * This function dynamically applies the test configuration parameters while the system is running.
	 * It is used in multicore systems where each CPU may have its own configuration.
	 *
	 */
	void STL_TSSP_set_test_config_runtime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T *);
	/**
	 * @brief Restore the runtime test configuration for a specific CPU.
	 * This function reverts any runtime test configuration modifications for a specific CPU.
	 * It is used in multicore systems where each CPU may have its own configuration.
	 * @note This function should be used with caution, as restoring the runtime test configuration
	 * may lead to system instability if the system hangs or becomes unresponsive.
	 */
	void STL_TSSP_restore_test_config_runtime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T *);

#else
/**
 * @brief Set the test configuration at boot time.
 * This function configures necessary parameters for a test before the test execution begins.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 */
void STL_TSSP_set_test_config_bootime(STL_SIZE_T test_number, STL_ERROR_T *);
/**
 * @brief Restore the test configuration set at boot time.
 * This function reverts the boot time test configuration to its original state.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 */
void STL_TSSP_restore_test_config_bootime(STL_SIZE_T test_number, STL_ERROR_T *);
/**
 * @brief Set the test configuration during runtime.
 * This function dynamically applies the test configuration parameters while the system is running.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 */
void STL_TSSP_set_test_config_runtime(STL_SIZE_T test_number, STL_ERROR_T *);
/**
 * @brief Restore the runtime test configuration.
 * This function reverts any runtime test configuration modifications.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 */
void STL_TSSP_restore_test_config_runtime(STL_SIZE_T test_number, STL_ERROR_T *);
#endif /*STL_MULTICORE_SOC*/

	/*****************************************************************************************************/
	/****************                    Test Setup Support Package                       ****************/
	/****************                           OS services                               ****************/
	/*****************************************************************************************************/

#if (STL_OS_PRESENT > 0u)
	/**
	 * @brief Create an OS task for test support.
	 * This function creates an operating system task intended to manage test operations.
	 * It is only available when OS support is enabled.
	 */
	void STL_TSSP_OS_task_create(void);
	/**
	 * @brief Delete an OS task.
	 * This function terminates and cleans up the OS task associated with test support.
	 * It is only available when OS support is enabled.
	 */
	void STL_TSSP_OS_task_delete(void);
#endif /*STL_OS_PRESENT*/

#if __cplusplus
}
#endif /*__cplusplus*/

#endif /*__STL_TSSP_H__*/
#endif /*__STL__*/