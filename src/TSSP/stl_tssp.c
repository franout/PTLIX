#if __STL__

#include "stl_tssp.h"
#include "stl_cfg.h"
#include "stl_sbst_cfg.h"
#include "stl_types.h"
#include "stl_test_setup.h"

#if STL_MULTICORE_EXECUTION
STATIC_KEYWORD STL_TSSP_TEST_SETUP_PTR_T tssp_bt_setup[STL_NUM_CPU][STL_TOT_BT_ROUTINE] = {sbst_bt_setup_1, sbst_bt_setup_2};
STATIC_KEYWORD STL_TSSP_TEST_RESTORE_PTR_T tssp_bt_restore[STL_NUM_CPU][STL_TOT_BT_ROUTINE] = {sbst_bt_restore_1, sbst_bt_restore_2};
STATIC_KEYWORD STL_TSSP_TEST_SETUP_PTR_T tssp_rt_setup[STL_NUM_CPU][STL_TOT_RT_ROUTINE] = {} ;
STATIC_KEYWORD STL_TSSP_TEST_RESTORE_PTR_T tssp_rt_restore[STL_NUM_CPU][STL_TOT_RT_ROUTINE] = {} ;
#else
STATIC_KEYWORD STL_TSSP_TEST_SETUP_PTR_T tssp_bt_setup[STL_TOT_BT_ROUTINE] = {sbst_bt_setup_1, sbst_bt_setup_2};
STATIC_KEYWORD STL_TSSP_TEST_RESTORE_PTR_T tssp_bt_restore[STL_TOT_BT_ROUTINE] = {sbst_bt_restore_1, sbst_bt_restore_2};
STATIC_KEYWORD STL_TSSP_TEST_SETUP_PTR_T tssp_rt_setup[STL_TOT_RT_ROUTINE] = {};
STATIC_KEYWORD STL_TSSP_TEST_RESTORE_PTR_T tssp_rt_restore[STL_TOT_RT_ROUTINE] = {};
#endif /*STL_MULTICORE_EXECUTION*/



/**
 * Test configuration specific function
 */
#if (STL_MULTICORE_SOC > 0u)
/**
 * @brief Set the test configuration at boot time for a specific CPU.
 * This function configures necessary parameters for a test before the test execution begins.
 * It is used in multicore systems where each CPU may have its own configuration.
 * @param cpu The target CPU for which the test configuration applies.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 *
 */
void STL_TSSP_set_test_config_bootime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of boot time test configuration logic for a specific CPU
	// This function is typically used to configure necessary parameters for a test
	// before the test execution begins.
	// The actual implementation will depend on the specific hardware platform and CPU architecture.
	tssp_bt_setup[cpu][test_number]();
    return;
}
/**
 * @brief Restore the test configuration set at boot time for a specific CPU.
 * This function reverts the boot time test configuration to its original state.
 * It is used in multicore systems where each CPU may have its own configuration.
 * @param cpu The target CPU whose configuration is restored.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 */
void STL_TSSP_restore_test_config_bootime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of restoring boot time test configuration logic for a specific CPU
	// This function is typically used to revert the boot time test configuration to its original state.
	// The actual implementation will depend on the specific hardware platform and CPU architecture.
	tssp_bt_restore[cpu][test_number]();
	return;
}
/**
 * @brief Set the test configuration during runtime for a specific CPU.
 * This function dynamically applies the test configuration parameters while the system is running.
 * It is used in multicore systems where each CPU may have its own configuration.
 * @param cpu The target CPU for the runtime configuration.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 */
void STL_TSSP_set_test_config_runtime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of runtime test configuration logic for a specific CPU
	// This function is typically used to dynamically apply the test configuration parameters while the system is
	// running. The actual implementation will depend on the specific hardware platform and CPU architecture.
	tssp_rt_setup[cpu][test_number]();
	return;
}
/**
 * @brief Restore the runtime test configuration for a specific CPU.
 * This function reverts any runtime test configuration modifications for a specific CPU.
 * It is used in multicore systems where each CPU may have its own configuration.
 * @param cpu The target CPU whose runtime configuration is restored.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 * @note This function should be used with caution, as restoring the runtime test configuration
 * may lead to system instability if the system hangs or becomes unresponsive.
 */
void STL_TSSP_restore_test_config_runtime(STL_CPUS cpu, STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of restoring runtime test configuration logic for a specific CPU
	// This function is typically used to revert any runtime test configuration modifications for a specific CPU.
	// The actual implementation will depend on the specific hardware platform and CPU architecture.
	tssp_rt_restore[cpu][test_number]();
	return;
}

#else
/**
 * @brief Set the test configuration at boot time.
 * This function configures necessary parameters for a test before the test execution begins.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 */
void STL_TSSP_set_test_config_bootime(STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of boot time test configuration logic
	// This function is typically used to configure necessary parameters for a test
	// before the test execution begins.
	// The actual implementation will depend on the specific hardware platform.
	tssp_bt_setup[test_number]();
	return;
}
/**
 * @brief Restore the test configuration set at boot time.
 * This function reverts the boot time test configuration to its original state.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 * @note This function should be used with caution, as restoring the boot time test configuration
 * may lead to system instability if the system hangs or becomes unresponsive.
 */
void STL_TSSP_restore_test_config_bootime(STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of restoring boot time test configuration logic
	// This function is typically used to revert the boot time test configuration to its original state.
	// The actual implementation will depend on the specific hardware platform.
	tssp_bt_restore[test_number]();
	return;
}
/**
 * @brief Set the test configuration during runtime.
 * This function dynamically applies the test configuration parameters while the system is running.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 * @param test_number Identifier for the specific test configuration.
 * @param error Pointer to a variable to store error status.
 */
void STL_TSSP_set_test_config_runtime(STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of runtime test configuration logic
	// This function is typically used to dynamically apply the test configuration parameters while the system is
	// running. The actual implementation will depend on the specific hardware platform.
	tssp_rt_setup[test_number]();
	return;
}
/**
 * @brief Restore the runtime test configuration.
 * This function reverts any runtime test configuration modifications.
 * It is used in single-core systems or when CPU-specific configurations are not required.
 * @param test_number Identifier for the test configuration.
 * @param error Pointer to a variable to store error status.
 * @note This function should be used with caution, as restoring the runtime test configuration
 * may lead to system instability if the system hangs or becomes unresponsive.
 */
void STL_TSSP_restore_test_config_runtime(STL_SIZE_T test_number, STL_ERROR_T * err)
{
	// Implementation of restoring runtime test configuration logic
	// This function is typically used to revert any runtime test configuration modifications.
	// The actual implementation will depend on the specific hardware platform.
	tssp_rt_restore[test_number]();
	return;
}
#endif /*STL_MULTICORE_SOC*/

#endif /*__STL__*/