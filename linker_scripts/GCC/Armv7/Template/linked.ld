/* 
 * This is a linker script template for GCC.
 * It defines the memory layout and sections for a typical embedded system.
 * Adjust the memory addresses and section names as needed for your project.
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Define the stack size and heap size */
__stack_size = 0x800; /* 2KB stack size */
__heap_size = 0x2000; /* 8KB heap size */
__stack_top = ORIGIN(RAM) + LENGTH(RAM) - __stack_size;
__heap_top = __stack_top - __heap_size;
__heap_start = __heap_top - __heap_size;
__stack_start = __stack_top;
__stack_end = __stack_top - __stack_size;
__heap_end = __heap_top - __heap_size;


SECTIONS
{
  . = 0x10000;
  .text : { *(.text) }
  . = 0x8000000;
  .data : { *(.data) }
  .bss : { *(.bss) }


  .stl_bootime : {
    *(.stl_bootime_code)
    *(.stl_bootime_data)
  } > FLASH

#if defined(STL_RELOCATION)
  .stl_runtime : {
    *(.stl_runtime_code)
    *(.stl_runtime_data)
  } > RAM AT > FLASH
#else
  .stl_runtime : {
    *(.stl_runtime_code)
    *(.stl_runtime_data)
  } > FLASH
#endf /*STL_RELOCATION*/

  .stl_test_header : {
    *(.stl_test_header_section)
  } > FLASH

  .stl_signature : {
    *(.stl_signature_section)
  } > RAM

  .stl_exception_table : {
    *(.stl_exception_table)
  } > FLASH

  .stl_exception_handlers : {
    *(.stl_exception_handlers)
  } > FLASH 

}