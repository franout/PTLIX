#if __STL__

#ifndef __STL_MODULE__
#define __STL_MODULE__

#include "stl.h"
#include "stl_cfg.h"
#include "stl_tssp.h"
#include "stl_sbst_cfg.h"

#if STL_RELOCATED

/**
 * @brief Relocation data for STL runtime tests.
 * This header contains the relocation entries for the STL runtime tests.
 * It is used to relocate the runtime test code from ROM into RAM.
 *
 */
#include "stl_relocation.h"

#endif /* STL_RELOCATED */

#if STL_BOOT_TEST
/**
 * @brief Pointer to the boot test routines.
 *
 * This array contains pointers to the boot test routines.
 * It is used to call the boot tests during the boot process.
 * The array is indexed by the STL_TOT_BT_ROUTINE enum.
 */
STL_FUNCT_PTR_T SBST_BT[STL_TOT_BT_ROUTINE];
#endif /* STL_BOOT_TEST */

#if STL_RUNTIME_TEST
/**
 * @brief Pointer to the runtime test routines.
 *
 * This array contains pointers to the runtime test routines.
 * It is used to call the runtime tests during the runtime process.
 * The array is indexed by the STL_TOT_RT_ROUTINE enum.
 */
STL_FUNCT_PTR_T SBST_RT[STL_TOT_RT_ROUTINE];
#endif /* STL_RUNTIME_TEST */

/**
 * @brief Initialize the STL module.
 *
 * This function initializes the STL module and its error management.
 *
 * @param[out] err Pointer to error variable.
 */
void STL_init(STL_ERROR_T *err)
{
	*err = STL_ERROR_NONE;
	STL_em_init(err);
	if (*err != STL_ERROR_NONE)
	{
		return;
	}
}

/**
 * @brief Deinitialize the STL module.
 *
 * This function deinitializes the STL module by deleting the OS task if present.
 *
 * @param[out] err Pointer to error variable.
 */
void STL_deinit(STL_ERROR_T *err)
{
	*err = STL_ERROR_NONE;
	STL_em_deinit(err);
	if (*err != STL_ERROR_NONE)
	{
		return;
	}
}

/**
 * @brief Relocate runtime test code.
 *
 * This function relocates the runtime test code from ROM into RAM.
 *
 * @param[out] err Pointer to error variable.
 */
void STL_relocate_runtime_tests(STL_ERROR_T *err)
{
#if STL_RELOCATED
	*err = STL_ERROR_NONE;
#if STL_RELOCATION_TABLE

	// Process each relocation entry from the table
	for (size_t i = 0; i < sizeof(relocationTable) / sizeof(relocationTable[0]); i++)
	{
		STL_TSSP_CPU_relocate(relocationTable[i].src, relocationTable[i].dst, relocationTable[i].size, err);
		if (*err != STL_ERROR_NONE)
		{
			return;
		}
	}
#else
	STL_ADDR_T *code_start = (STL_ADDR_T *)&__stl_ram_code_start__;
	STL_ADDR_T *code_end = (STL_ADDR_T *)&__stl_ram_data_end__;
	STL_INT32U_T size = code_end - code_start;
	STL_TSSP_CPU_relocate(stl_src, code_start, size, err);
	if (*err != STL_ERROR_NONE)
	{
		return;
	}
#endif /* STL_RELOCATION_TABLE */
#else
	*err = STL_ERROR_NOT_IMPLEMENTED;
#endif /* STL_RELOCATED */
}

/**
 * @brief Create an OS task for STL runtime.
 *
 * This function creates an OS task for runtime tests if the OS is present.
 *
 * @param[out] err Pointer to error variable.
 */
#if STL_OS_PRESENT
void STL_runtime_OS_task_create(STL_ERROR_T *err)
{
	*err = STL_ERROR_NONE;

	STL_al_OS_task_create(err);
}
/**
 * @brief Delete the OS task for STL runtime.
 *
 * This function deletes the task in the operating system that was created for executing the STL runtime tests.
 *
 * @param[out] err Pointer to error variable.
 */
void STL_runtime_OS_task_delete(STL_ERROR_T *err)
{
	*err = STL_ERROR_NONE;
	STL_al_OS_task_delete(err);
}

#endif /* STL_OS_PRESENT */

#endif /* __STL_MODULE__ */
#endif /* __STL__ */
