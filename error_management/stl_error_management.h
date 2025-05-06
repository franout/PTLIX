#if __STL__
#ifndef __STL_EM__MODULE__
#define __STL_EM__MODULE__
#include "stl_cfg.h"

#if STL_ERROR_MANAGEMENT_ENABLED
/*
 * static internal structure for signature and error colleciton
 *
 * */



#include "stl.h"

#include "stl_al_os.h"
#include "stl_tssp.h"
#include "stl_core.h"


#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

typedef struct {
	STL_SIGNATURE_T sig;
	STL_BOOL mismatch;
} STL_EM_TEST_T;

void STL_em_init(STL_ERROR_T *err) ;
STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu, STL_ERROR_T *err);

void STL_em_failed_runtime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect,
		STL_ERROR_T *err) ;

void STL_em_failed_bootime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect,
		STL_ERROR_T *err) ;
STL_SIGNATURE_T STL_em_bt_get_signature(STL_CPUS cpu, STL_SIZE_T index,
		STL_ERROR_T *err) ;

STL_SIGNATURE_T STL_em_rt_get_signature(STL_CPUS cpu, STL_SIZE_T index,
		STL_ERROR_T *err) ;


#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*STL_ERROR_MANAGEMENT_ENABLED*/
#endif /*__STL_EM__MODULE__*/
#endif /*__STL__*/
