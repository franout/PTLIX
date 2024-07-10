/*
 * Software Test Library for SPC58 family
 *
 * */

#ifndef __STL_H__
#define __STL_H__

#if __STL__
#include "stl_cfg.h"
#include "stl_types.h"
#include "stl_tssp.h"


typedef struct {
	SLT_INT32U_T index;
	STL_SIGNATURE_T signature;
}STL_FAILED_TEST_T;


/*Application Programming Interface definition*/
void STL_init(STL_ERROR_T *err );
void STL_deinit(STL_ERROR_T *err );
void STL_relocate_runtime_tests(STL_ERROR_T * err);


void STL_schedule_runtime(STL_CPUS cpu,STL_ERROR_T *err);
void STL_schedule_bootime(STL_CPUS cpu,STL_ERROR_T *err);

#if STL_RELOCATED
void STL_runtime_load(STL_ERROR_T *err);
#endif /*__STL_RELOCATED__*/

#if STL_OS_PRESENT
void STL_runtime_OS_task_create(STL_ERROR_T *err);
#endif /*__STL_IN_OS__*/


#if STL_ERROR_MANAGEMENT_ENABLED
/*Error Management*/
STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu,STL_ERROR_T *err);
STL_SIZE_T STL_em_bootitme_failed(STL_CPUS cpu,STL_ERROR_T *err);
void STL_em_failed_runtime_all(STL_CPUS cpu,STL_FAILED_TEST_T * vect,STL_ERROR_T *err);
void STL_em_failed_bootime_all(STL_CPUS cpu,STL_FAILED_TEST_T * vect,STL_ERROR_T *err);
STL_SIGNATURE_T STL_em_get_signature (STL_CPUS cpu,STL_SIZE_T index,STL_ERROR_T *err);
#endif /*STL_ERROR_MANAGEMENT_ENABLED*/

#endif /*__STL__*/
#endif /* __STL_H__ */
