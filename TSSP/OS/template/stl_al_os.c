#if __STL__
#include "stl_al_os.h"
#include "stl_cfg.h"
#include "stl_types.h"

#ifndef STL_AL_OS_MODULE
#define STL_AL_OS_MODULE

#if (STL_OS_PRESENT > 0u)

/**
 * @brief Create an OS task for test support.
 * This function creates an operating system task intended to manage test operations.
 * It is only available when OS support is enabled.
 * The actual implementation will depend on the specific OS being used.
 * @note Ensure that the OS is properly initialized before calling this function.
 * @return void
 * @warning This function should be used with caution, as improper task creation
 * may lead to system instability or resource leaks.
 */
void STL_TSSP_OS_task_create(void)
{
	// Implementation of OS task creation logic
	// This function is typically used to create an OS task
	// that will handle test operations.
	// The actual implementation will depend on the specific OS being used.
	return;
}
/**
 * @brief Delete an OS task.
 * This function terminates and cleans up the OS task associated with test support.
 * It is only available when OS support is enabled.
 * The actual implementation will depend on the specific OS being used.
 * @note Ensure that the OS task is no longer needed before calling this function.
 * @return void
 * @warning This function should be used with caution, as improper task deletion
 * may lead to resource leaks or system instability.
 *
 */
void STL_TSSP_OS_task_delete(void)
{
	// Implementation of OS task deletion logic
	// This function is typically used to terminate and clean up the OS task
	// associated with test support.
	// The actual implementation will depend on the specific OS being used.
	return;
}

#endif /* STL_OS_PRESENT */

#endif /* STL_AL_OS_MODULE */
#endif /*__STL__*/