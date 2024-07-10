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

typedef struct {
	STL_SIGNATURE_T sig;
	STL_BOOL mismatch;
} STL_EM_TEST_T;


#if STL_MULTICORE_EXECUTION
static STL_EM_TEST_T em_bt_sign [STL_TOT_BT_ROUTINE][STL_NUM_CPU] ;
static STL_EM_TEST_T em_rt_sign [STL_TOT_RT_ROUTINE][STL_NUM_CPU] ;
#else
static STL_EM_TEST_T em_bt_sign[STL_TOT_BT_ROUTINE] ;
static STL_EM_TEST_T em_rt_sign[STL_TOT_RT_ROUTINE];
#endif /*STL_MULTICORE_EXECUTION*/

void STL_em_init(STL_ERROR_T *err) {
	*err = STL_ERROR_NONE;
#if STL_ERROR_MANAGEMENT_ENABLED
	STL_SIZE_T i, j;

#if STL_MULTICORE_EXECUTION
for (j=0;j<STL_NUM_CPU;j++){
for(i=0;i<STL_BOOTTIME_ROUTINES;i++){
	em_bt_sign[j][i].sig=0;
	em_bt_sign[j][i].mismatch=STL_FALSE;
}

for(i=0;i<STL_RUNTIME_ROUTINES;i++){
	em_rt_sign[j][i].sig=0;
	em_rt_sign[j][i].mismatch=STL_FALSE;
}
}
#else
	for (i = 0; i < STL_TOT_BT_ROUTINE; i++) {
		em_bt_sign[i].sig=0;
		em_bt_sign[i].mismatch=STL_FALSE;
	}

	for (i = 0; i < STL_TOT_RT_ROUTINE; i++) {
		em_rt_sign[i].sig=0;
		em_rt_sign[i].mismatch=STL_FALSE;
	}
#endif /* STL_MULTICORE_EXECUTION*/

#endif /*STL_ERROR_MANAGEMENT_ENABLED*/

}

STL_SIZE_T STL_em_runtime_failed(STL_CPUS cpu, STL_ERROR_T *err) {
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++) {
		if (em_rt_sign[cpu][j].mismatch == STL_TRUE) {
			return j;
		}
	}
#else
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++) {
			if (em_rt_sign[j].mismatch == STL_TRUE) {
				return j;
			}
		}
#endif /*STL_MULTICORE_EXECUTION*/
	return -1;
}
STL_SIZE_T STL_em_bootitme_failed(STL_CPUS cpu, STL_ERROR_T *err) {
	STL_SIZE_T j;
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	/*cause the master core will wait for booting the OS*/
	for (i = 0; i < STL_NUM_CPU; i++) {
		for (j = 0; j < STL_TOT_BT_ROUTINE; j++) {
			if (em_bt_sign[i][j].mismatch == STL_TRUE) {
				return j;
			}
		}
	}
#else
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++) {
			if (em_bt_sign[j].mismatch == STL_TRUE) {
				return j;
			}
		}
#endif /*STL_MULTICORE_EXECUTION*/
	return -1;

}
void STL_em_failed_runtime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect,
		STL_ERROR_T *err) {
	STL_SIZE_T j;
	*err=STL_ERROR_NONE;
#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++) {
				if (em_rt_sign[cpu][j].mismatch == STL_TRUE) {
					vect[j].index=j;
					vect[j].signature=em_rt_sign[cpu][j].sig;
				}
			}
#else
	for (j = 0; j < STL_TOT_RT_ROUTINE; j++) {
					if (em_rt_sign[j].mismatch == STL_TRUE) {
						vect[j].index=j;
						vect[j].signature=em_rt_sign[j].sig;
					}
				}
#endif /*STL_MULTICORE_EXECUTION*/

}
void STL_em_failed_bootime_all(STL_CPUS cpu, STL_FAILED_TEST_T *vect,
		STL_ERROR_T *err) {
	STL_SIZE_T j;
	*err=STL_ERROR_NONE;
#if STL_MULTICORE_EXECUTION
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++) {
				if (em_bt_sign[cpu][j].mismatch == STL_TRUE) {
					vect[j].index=j;
					vect[j].signature=em_bt_sign[cpu][j].sig;
				}
			}
#else
	for (j = 0; j < STL_TOT_BT_ROUTINE; j++) {
					if (em_bt_sign[j].mismatch == STL_TRUE) {
						vect[j].index=j;
						vect[j].signature=em_bt_sign[j].sig;
					}
				}
#endif /*STL_MULTICORE_EXECUTION*/
}
STL_SIGNATURE_T STL_em_bt_get_signature(STL_CPUS cpu, STL_SIZE_T index,
		STL_ERROR_T *err) {
#if STL_MULTICORE_EXECUTION
	if (cpu < 0 || cpu > STL_NUM_CPU) {
		*err = STL_CPU_OUT_OF_BOUNDS;
		return 0;
	}
#endif /*STL_MULTICORE_EXECUTION*/
	if (index < 0 || index > STL_TOT_BT_ROUTINE) {
		*err = STL_INDEX_OUT_OF_BOUNDS;
		return 0;
	}
	*err = STL_ERROR_NONE;
#if STL_MULTICORE_EXECUTION
	return em_bt_sign[cpu][index].sig;
#else
	return em_bt_sign[index].sig;
#endif /*STL_MULTICORE_EXECUTION*/
}

STL_SIGNATURE_T STL_em_rt_get_signature(STL_CPUS cpu, STL_SIZE_T index,
		STL_ERROR_T *err) {
#if STL_MULTICORE_EXECUTION
	if (cpu < 0 || cpu > STL_NUM_CPU) {
		*err = STL_CPU_OUT_OF_BOUNDS;
		return 0;
	}
#endif /*STL_MULTICORE_EXECUTION*/
	if (index < 0 || index > STL_TOT_RT_ROUTINE) {
		*err = STL_INDEX_OUT_OF_BOUNDS;
		return 0;
	}
	*err = STL_ERROR_NONE;

#if STL_MULTICORE_EXECUTION
	return em_rt[cpu][index].sig;
#else
	return em_rt_sign[index].sig;
#endif /*STL_MULTICORE_EXECUTION*/

}

#endif /*STL_ERROR_MANAGEMENT_ENABLED*/

#endif /*__STL_EM__MODULE__*/
#endif /*__STL__*/
