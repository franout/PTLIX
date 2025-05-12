#if __STL__

#ifndef __STL_AL_CPU_H__
#define __STL_AL_CPU_H__
#include "stl_cfg.h"
#include "stl_types.h"


#if __cplusplus
extern "C"
{
#endif /*__cplusplus*/

    void STL_hal_CPU_restore_ivor(void);

    void STL_hal_CPU_swap_ivor(void);

#if STL_USE_MPU
    typedef enum
    {
        STL_CPU_MPU_ACCESS_NONE = 0u,    /* No access permissions */
        STL_CPU_MPU_ACCESS_READ = 1u,    /* Read access permission */
        STL_CPU_MPU_ACCESS_WRITE = 2u,   /* Write access permission */
        STL_CPU_MPU_ACCESS_EXECUTE = 4u, /* Execute access permission */
        STL_CPU_MPU_ACCESS_ALL = 7u      /* All access permissions (read, write, execute) */
    } STL_CPU_MPU_ACCESS_t;

    typedef struct
    {
        uint32_t base_address;       /* Base address of the region */
        uint32_t size;               /* Size of the region */
        STL_CPU_MPU_ACCESS_t access; /* Access permissions for the region */
    } STL_CPU_MPU_CFG_t;

    void STL_hal_CPU_configure_mpu(STL_CPU_MPU_CFG_t *mpu_cfg);
#endif /*STL_USE_MPU*/

#if __cplusplus
}
#endif /*__cplusplus*/

#endif /*__STL_AL_CPU_H__*/
#endif /*__STL__*/