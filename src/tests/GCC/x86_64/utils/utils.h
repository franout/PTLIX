#ifndef __X86_UTILS_H__
#define __X86_UTILS_H__
/**
 * * @file utils.h
 * * @brief This file contains utility macros for X86 ABI prologue and epilogue.
 * * These macros are used to manage the stack frame and register saving/restoring
 * * in X86 assembly functions.
 * 
 */

/* @macro X86_ABI_EPILOGUE
 * @brief Macro to restore the stack pointer and return from a function.
 * 
 * This macro restores the stack pointer and the saved registers
 * before returning from a function. It is typically used at the end of a function
 * to clean up the stack frame.
 */
.macro X86_ABI_EPILOGUE
    // Restore the stack pointer and return
    
.endm

/**
 * 
 * @macro X86_ABI_PROLOGUE
 * @brief Macro to save registers and set up the stack frame at the beginning of a function.
 * 
 * This macro adjusts the stack pointer and saves the registers that
 * will be used in the function. It is typically used at the start of a function to
 * prepare for local variable storage and register usage.

*/
.macro X86_ABI_PROLOGUE
    // Save the registers and stack pointer
.endm

/**
 * @macro X86_ABI_SAVE_REGISTERS
 * @brief Macro to save additional registers in the stack frame.
 * 
 * This macro saves the registers onto the stack. It is used
 * when more registers need to be preserved across function calls.
 */
.macro X86_ABI_SAVE_REGISTERS
    // Save additional registers
.endm   
/**
 * @macro X86_ABI_RESTORE_REGISTERS
 * @brief Macro to restore additional registers from the stack frame.
 * 
 * This macro restores the registers from the stack. It is used
 * to clean up the stack frame after the function has completed its operations.
 */
.macro X86_ABI_RESTORE_REGISTERS
    // Restore additional registers
.endm
/**
 * @macro COMPUTE_SIGNATURE
 * @brief Macro to compute a signature based on the operation.
 * * This macro is a placeholder for actual signature computation logic.
 * * It could be a simple XOR of the operands or some other operation.
 * * The actual implementation will depend on the specific requirements of the signature computation.
 * * @note This macro is called verbosely at every operation in the sbst core.
 * * @return The computed signature in register.
 */
.macro COMPUTE_SIGNATURE // this could be a macro (called verbosily at every operation in the sbst core)
    // Compute the signature based on the operation
    // This is a placeholder for actual signature computation logic
    
.endm

/**
 * @macro CHECK_SIGNATURE
 * @brief Macro to check the signature against a predefined value.
 * * This macro is a placeholder for actual signature checking logic.
 * It could compare the computed signature against a predefined value or perform some validation.
 * * The actual implementation will depend on the specific requirements of the signature checking.
 * * @note This macro is called at the end of the sbst core to validate the signature.
 * * @return The result of the signature check.
 * * The result could be a boolean value indicating whether the signature is valid or not.
 * * The actual implementation will depend on the specific requirements of the signature checking.
*/
.macro CHECK_SIGNATURE 
    // Check the signature against a predefined value
    // This is a placeholder for actual signature checking logic
.endm 

#endif /* __X86_UTILS_H__ */