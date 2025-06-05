#if __STL__


#ifndef __STL_MODULE__
#define __STL_MODULE__

#include "stl.h"
#include "stl_cfg.h"
#include "stl_al_os.h"
#include "stl_tssp.h"
#include "stl_core.h"

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

#if STL_RELOCATION_TABLE
	// TODO add a table for multiple relocation in case of error
#endif /*STL_RELOCATION_TABLE*/

#endif /*STL_RELOCATED*/

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

}
void STL_deinit(STL_ERROR_T *err ){

#if STL_OS_PRESENT
	/*delete task */
	STL_al_OS_task_delete(err);
#endif /**/

}


void STL_relocate_runtime_tests(STL_ERROR_T * err){
#if STL_RELOCATED

	*err=STL_ERROR_NONE;
#if STL_RELOCATION_TABLE
	// TODO add a table handling for multiple relocation in case of error
#else
	STL_ADDR_T *  code_start = (STL_ADDR_T *) &__stl_ram_code_start__;
	STL_ADDR_T *  code_end = (STL_ADDR_T *) &__stl_ram_data_end__;
	STL_INT32U_T size=code_end-code_start;
	STL_TSSP_CPU_relocate(stl_src,code_start,size ,err);
	if (*err!=STL_ERROR_NONE){
		return ;
	}
#endif  /*STL_RELOCATION_TABLE*/
#else
	*err=STL_ERROR_NOT_IMPLEMENTED;
#endif /*STL_RELOCATED*/
}


void STL_runtime_OS_task_create(STL_ERROR_T * err){
#if STL_OS_PRESENT
	STL_al_OS_task_create(err);
#endif /*__STL_IN_OS__*/
}



#endif /*__STL_MODULE__*/
#endif /*__STL__*/
