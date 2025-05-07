#if __STL__

#ifndef __STL_AL_OS_H__
#define __STL_AL_OS_H__
#include "stl_cfg.h"
#include "stl_types.h"


#if __cplusplus
extern "C"
{
#endif /*__cplusplus*/

#if (STL_OS_PRESENT > 0u)
    void STL_hal_OS_task_create(void);
    void STL_hal_OS_task_delete(void);
#endif /*STL_OS_PRESENT*/
#if __cplusplus
}
#endif /*__cplusplus*/
#endif /*__STL_AL_OS_H__*/
#endif /*__STL__*/
/* OS related*/
