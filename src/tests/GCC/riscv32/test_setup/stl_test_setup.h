#if __STL__

#ifndef __SBST_TEST_SETUP_H__
#define __SBST_TEST_SETUP_H__

#include "stl_tssp.h"
#include "stl_cfg.h"
#include "stl_types.h"
#include "stl_sbst_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set up boot time test configuration for the first CPU.
 *
 * This function is typically used to configure the system for boot time tests.
 */
void sbst_bt_setup_1(void);

/**
 * @brief Set up boot time test configuration for the second CPU.
 *
 * This function is typically used to configure the system for boot time tests.
 */
void sbst_bt_setup_2(void);

/**
 * @brief Restore boot time test configuration for the first CPU.
 *
 * This function reverts any changes made during the boot time test setup phase.
 */
void sbst_bt_restore_1(void);

/**
 * @brief Restore boot time test configuration for the second CPU.
 *
 * This function reverts any changes made during the boot time test setup phase.
 */
void sbst_bt_restore_2(void);

#ifdef __cplusplus
}
#endif

#endif /* __SBST_TEST_SETUP_H__ */
#endif /* __STL__ */