#if __STL__

#ifndef __STL_SBST_CFG_H__
#define __STL_SBST_CFG_H__

/****************                    SBST Configuration                               ****************/

/**
 * @brief Total number of boot-time routines.
 * This macro defines the total number of boot-time routines available in the SBST.
 * It is used to allocate memory and manage the boot-time routines in the SBST framework.
 * @note This value should be set according to the number of boot-time routines implemented.
 * @ingroup SBST
 */
#define STL_TOT_BT_ROUTINE 0u /* Total number of boot-time routines */
/**
 * @brief Total number of runtime routines.
 * This macro defines the total number of runtime routines available in the SBST.
 * It is used to allocate memory and manage the runtime routines in the SBST framework.
 * @note This value should be set according to the number of runtime routines implemented.
 * @ingroup SBST
 */
#define STL_TOT_RT_ROUTINE 1u /* Total number of runtime routines */

#endif /*__STL_SBST_CFG_H__*/
#endif /*__STL__*/
