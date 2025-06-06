#if __STL__

#ifndef __STL_RT_RELOCATION_H__
#define __STL_RT_RELOCATION_H__

// Include common configuration and type definitions
#include "stl_config.h"
#include "stl_types.h"

#if (STL_RELOCATED > 0u)

/**
 * @brief External relocation symbols.
 *
 * The following symbols must be defined in the linker script.
 * They represent the start addresses and sizes of the ROM and RAM sections
 * that will be used for runtime relocation of STL code and data.
 *
 * Note: Do not modify the definitions in the linker script.
 */
extern STL_ADDR_T __stl_ram_data_start__;
extern STL_ADDR_T __stl_ram_data_size__;

extern STL_ADDR_T __stl_ram_code_start__;
extern STL_ADDR_T __stl_ram_code_size__;

extern STL_ADDR_T __stl_ram_data_end__;
extern STL_ADDR_T __stl_rom_start__;

extern STL_ADDR_T _stl_lib;

// Pointers used to mark the source (ROM) and target (RAM) relocation addresses.
EXTERN_KEYWORD STL_ADDR_T *stl_src = &__stl_rom_start__;
EXTERN_KEYWORD STL_ADDR_T *stl_ram_data = &__stl_ram_data_start__;
EXTERN_KEYWORD STL_ADDR_T *stl_ram_code = &__stl_ram_code_start__;
EXTERN_KEYWORD STL_ADDR_T *stl_lib = &_stl_lib;

#if (STL_RELOCATION_TABLE > 0u)

#include "stl_types.h" // Ensure STL types are defined

/**
 * @brief Structure defining a relocation entry.
 *
 * Each entry specifies the source address in ROM, the destination address in RAM,
 * and the size of the code/data block to relocate.
 */
typedef struct
{
	STL_ADDR_T *src;   ///< Source address (ROM)
	STL_ADDR_T *dst;   ///< Destination address (RAM)
	STL_INT32U_T size; ///< Size of the block to relocate
} STL_RelocationEntry_T;

/**
 * @brief Table of relocation entries.
 *
 * This table defines the memory blocks that need to be relocated at runtime.
 * For each entry, data is copied from the source (ROM) to the destination (RAM).
 */
EXTERN_KEYWORD STL_RelocationEntry_T relocationTable[] = {
	// Relocate runtime test code: from ROM (stl_src) to RAM (stl_ram_code)
	// This can be used to copy code portions that need to be executed from different RAM locations.
	{stl_src, stl_ram_code, (STL_INT32U_T)(&__stl_ram_code_size__)},
};

#endif /* STL_RELOCATION_TABLE */

#endif /* STL_RELOCATED */
#endif /* __STL_RT_RELOCATION_H__ */

#endif /* __STL__ */