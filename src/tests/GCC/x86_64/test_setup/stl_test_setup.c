#if __STL__

#include "stl_tssp.h"
#include "stl_cfg.h"
#include "stl_types.h"
#include "stl_sbst_cfg.h"

#ifndef _SBST_TEST_SETUP_MODULE_
#define _SBST_TEST_SETUP_MODULE_
/**
 * @file template.c
 * @brief Template for Test Setup Support Package (TSSP) functions. 
 * This file provides a template for implementing the setup and restore functions
 * for boot time tests in the TSSP framework.
 * These functions are typically used to configure the system
 * for boot time tests and restore the original configuration after the tests are completed.
 * The actual implementation will depend on the specific hardware platform and test requirements.
 * @note Ensure that the functions are implemented according to the specific requirements of the TSSP framework.
 * @warning This file is a template and should be modified to suit the specific needs of the TSSP implementation.
 * @see TSSP documentation for more details on the Test Setup Support Package.
 * @ingroup TSSP
 */

void sbst_bt_setup_1(void)
{
    // Implementation of the function.
    // This function is typically used to set up the boot time test configuration for the first CPU.
    // The actual implementation will depend on the specific hardware platform.
    // For example, it may configure the interrupt vector table or set specific registers.
    // This function is called during the boot time test setup phase.

}


void sbst_bt_setup_2(void)
{
    // Implementation of the function.
    // This function is typically used to set up the boot time test configuration for the second CPU.
}

void sbst_bt_restore_1(void)
{
    // Implementation of the function.
    // This function is typically used to restore the boot time test configuration for the first CPU.
    // It reverts any changes made during the setup phase.
    // The actual implementation will depend on the specific hardware platform.
    // For example, it may restore the interrupt vector table or reset specific registers.  
}

void sbst_bt_restore_2(void)
{
    // Implementation of the function.
    // This function is typically used to restore the boot time test configuration for the second CPU.
    // It reverts any changes made during the setup phase.
    // The actual implementation will depend on the specific hardware platform.
    // For example, it may restore the interrupt vector table or reset specific registers.  
}

#endif /*_SBST_TEST_SETUP_MODULE_*/
#endif /*__STL__*/