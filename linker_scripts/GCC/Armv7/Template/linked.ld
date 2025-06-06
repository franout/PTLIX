/*
 * Linker Script Documentation
 *
 * This template configures the memory layout, sections, and entry point for an embedded ARM system.
 *
 * Output Format and Architecture:
 *   - OUTPUT_FORMAT: Defines the object file format as "elf32-littlearm".
 *   - OUTPUT_ARCH: Sets the target architecture as ARM.
 *   - ENTRY: Sets the starting point of execution to the symbol _start.
 *
 * Memory Regions:
 *   - FLASH: Designated as read/execute (rx) memory, beginning at 0x08000000 with a size of 512K.
 *   - RAM: Configured as read/write/execute (rwx) memory, starting at 0x20000000 with a size of 128K.
 *
 * Stack and Heap Configuration:
 *   - __stack_size: Specifies the size of the stack (2KB).
 *   - __heap_size: Specifies the size of the heap (8KB).
 *   - __stack_top: Computed as the end of RAM minus the stack size.
 *   - __heap_top, __heap_start, __stack_start, __stack_end, __heap_end:
 *       These symbols define the boundaries and layout of the stack and heap areas, ensuring proper allocation.
 *
 * Section Allocation:
 *   - The script assigns sections at specific addresses.
 *   - .text: For executable code.
 *   - .data: For initialized data.
 *   - .bss: For uninitialized data.
 *
 * Additional Sections for Project-Specific Data:
 *   - .stl_bootime:
 *       Contains boot time code and data, placed in FLASH.
 *   - .stl_runtime:
 *       Contains runtime code and data. Its location shifts between RAM and FLASH based on the STL_RELOCATION flag.
 *   - .stl_test_header:
 *       Stores test header information, allocated to FLASH.
 *   - .stl_signature:
 *       Holds the signature area, placed in RAM.
 *   - .stl_exception_table & .stl_exception_handlers:
 *       Define areas for exception management, both allocated to FLASH.
 *
 * Note:
 *   Adjust this template as needed to match the specific memory constraints and section requirements of your project.
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 128K
  /* Added new RAM region for relocated runtime code */
  RAM2 (rwx) : ORIGIN = 0x20020000, LENGTH = 64K
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

  .stl_runtime2 : {
    *(.stl_runtime2_code)
    *(.stl_runtime2_data)
  } > RAM2 AT > FLASH
#else
  .stl_runtime : {
    *(.stl_runtime_code)
    *(.stl_runtime_data)
    *(.stl_runtime2_code)
    *(.stl_runtime2_data)
  } > FLASH
#endif /*STL_RELOCATION*/

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
