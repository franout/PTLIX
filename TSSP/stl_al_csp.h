#if __STL__

#ifndef __STL_AL_CSP_H__
#define __STL_AL_CSP_H__
#include "stl_cfg.h"
#include "stl_types.h"


#if __cplusplus
extern "C"
{
#endif /*__cplusplus*/

#if STL_USE_WATCHDOG > 0u

#if STL_USE_FINE_GRAINED_WATCHDOG > 0u
    void STL_hal_CSP_watchdog_init(int32_t timeout_value, int32_t reset_value);
#else 
    void STL_hal_CSP_watchdog_init(void);
#endif /*STL_USE_FINE_GRAINED_WATCHDOG*/
    void STL_hal_CSP_watchdog_start(void);
    void STL_hal_CSP_watchdog_stop(void);
    void STL_hal_CSP_watchdog_reset(void);
#endif /*STL_USE_WATCHDOG*/

#if __cplusplus
}
#endif /*__cplusplus*/


#endif /*__STL_AL_CSP_H__*/
#endif /*__STL__*/
