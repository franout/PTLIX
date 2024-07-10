#if __STL__


#ifndef __STL_MODULE__
#define __STL_MODULE__

#include "stl.h"
#include "stl_cfg.h"
#include "stl_al_os.h"
#include "stl_tssp.h"
#include "stl_core.h"


#if STL_BOOT_TEST
extern STL_FUNCT_PTR_T SBST_BT [STL_TOT_BT_ROUTINE];
#endif /*STL_BOOT_TEST*/
#if STL_RUNTIME_TEST
extern STL_FUNCT_PTR_T SBST_RT [STL_TOT_RT_ROUTINE];
#endif /*STL_RUNTIME_TEST*/

void STL_init(STL_ERROR_T *err ){
	*err=STL_ERROR_NONE;
	STL_em_init(err);
	if (*err!=STL_ERROR_NONE)
	{
		return ;
	}

	/*create task for OS*/
#if STL_OS_PRESENT

#endif /*STL_OS_PRESENT*/

}
void STL_deinit(STL_ERROR_T *err ){


#if STL_OS_PRESENT
	/*delete task */

#endif /**/

}



#if STL_RELOCATED

/*they MUST BE IMPLEMENTED IN THE LINKER SCRIPT */
/*defined in the linker */
extern STL_ADDR_T __stl_ram_data_start__;
extern STL_ADDR_T __stl_ram_data_size__;

extern STL_ADDR_T __stl_ram_code_start__;
extern STL_ADDR_T __stl_ram_code_size__;
extern STL_ADDR_T __stl_ram_data_end__;
extern STL_ADDR_T __stl_rom_start__;

extern STL_ADDR_T _stl_lib;

STL_ADDR_T * stl_src = &__stl_rom_start__ ;
STL_ADDR_T *stl_ram_data = &__stl_ram_data_start__;
STL_ADDR_T *stl_ram_code = &__stl_ram_code_start__ ;
STL_ADDR_T *stl_lib=&_stl_lib;


#endif /*STL_RELOCATED*/





void STL_relocate_runtime_tests(STL_ERROR_T * err){
#if STL_RELOCATED

	*err=STL_ERROR_NONE;
#if STL_RELOCATION_TABLE
	// tood add a table for multiple relocation in case of error
#else
	STL_ADDR_T *  code_start = (STL_ADDR_T *) &__stl_ram_code_start__;
	STL_ADDR_T *  code_end = (STL_ADDR_T *) &__stl_ram_data_end__;
	SLT_INT32U_T size=code_end-code_start;
	STL_hal_CPU_relocate(stl_src,code_start,size ,err);
	if (*err!=STL_ERROR_NONE){
		return ;
	}
#endif  /*STL_RELOCATION_TABLE*/
#else
	*err=STL_ERROR_NOT_IMPLEMENTED;
#endif /*STL_RELOCATED*/
}


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
#ifndef __INJECTION__
		return ;
#else
		stl_signature_mismatch=1;
		ERROR_Trap();
#endif /*__INJECTION__*/
		}
	}

	if (index>=STL_TOT_RT_ROUTINE){
		index=0;
	}

#endif /*STL_RUNTIME_TEST*/

}
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
#ifndef __INJECTION__
		return ;
#else
		stl_signature_mismatch=1;
		ERROR_Trap();
#endif /*__INJECTION__*/
		}
	}
	STL_hal_CPU_restore_ivor();
#endif /*STL_BOOT_TEST*/
}



void STL_runtime_OS_task_create(STL_ERROR_T * err){
#if STL_OS_PRESENT
	STL_al_OS_task_create(err);
#endif /*__STL_IN_OS__*/
}



#endif /*__STL_MODULE__*/
#endif /*__STL__*/
