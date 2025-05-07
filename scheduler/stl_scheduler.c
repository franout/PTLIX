#if __STL__
#ifndef __STL_SCHEDULER__MODULE__
#define __STL_SCHEDULER__MODULE__
#include "stl_cfg.h"

//TODO implement different scheduler types for the runtime tests 
void STL_schedule_runtime(STL_CPUS cpu,STL_ERROR_T *err){
	static STL_SIZE_T index=0;
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;
	*err=STL_ERROR_NONE;
#if STL_RUNTIME_TEST==0
	*err=SLT_NO_RT_ROUTINE;
	return;
#else
	for(i=index;i<STL_RT_CHUNK && index<STL_TOT_RT_ROUTINE;i++){
		signature=SBST_RT[i]();
		STL_em_update_sig(i,signature,*err);
		if (*err!=STL_ERROR_NONE){
    		return ;
		}
	}

	if (index>=STL_TOT_RT_ROUTINE){
		index=0;
	}

#endif /*STL_RUNTIME_TEST*/

}
//TODO implement the muli cpu scheduler and signature update
void STL_schedule_bootime(STL_CPUS cpu,STL_ERROR_T *err){
	STL_SIZE_T i;
	STL_SIGNATURE_T signature;
	*err=STL_ERROR_NONE;
#if STL_BOOT_TEST==0
	*err=SLT_NO_BT_ROUTINE;
	return;
#else

	STL_hal_CPU_swap_ivor();
	for(i=0;i<STL_TOT_BT_ROUTINE;i++){
		signature=SBST_BT[i]();
		STL_em_update_sig(i,signature,*err);

		if (*err!=STL_ERROR_NONE){
		    return ;
		}
	}
	STL_hal_CPU_restore_ivor();
#endif /*STL_BOOT_TEST*/
}


#endif /*__STL_SCHEDULER_MODULE__*/
#endif /*__STL__*/