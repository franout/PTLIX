#ifndef __RISCV_UTILS_H__
#define __RISCV_UTILS_H__
/**
 * * @file utils.h
 * * @brief This file contains utility macros for RISC-V ABI prologue and epilogue.
 * * These macros are used to manage the stack frame and register saving/restoring
 * * in RISC-V assembly functions.
 * 
 */

/* @macro RISCV_ABI_EPILOGUE
 * @brief Macro to restore the stack pointer and return from a function.
 * 
 * This macro restores the stack pointer and the saved registers (ra, s0, s1, s2)
 * before returning from a function. It is typically used at the end of a function
 * to clean up the stack frame.
 */
.macro RISCV_ABI_EPILOGUE
    // Restore the stack pointer and return
    li a0, 0
    addi sp, sp, 16
    lw ra, 12(sp)
    lw s0, 8(sp)
    lw s1, 4(sp)
    lw s2, 0(sp)
    ret
.endm

/**
 * 
 * @macro RISCV_ABI_PROLOGUE
 * @brief Macro to save registers and set up the stack frame at the beginning of a function.
 * 
 * This macro adjusts the stack pointer and saves the registers (ra, s0, s1, s2) that
 * will be used in the function. It is typically used at the start of a function to
 * prepare for local variable storage and register usage.

*/
.macro RISCV_ABI_PROLOGUE
    // Save the registers and stack pointer
    addi sp, sp, -16
    sw s2, 0(sp)
    sw s1, 4(sp)
    sw s0, 8(sp)
    sw ra, 12(sp)
    
.endm

/**
 * @macro RISCV_ABI_SAVE_REGISTERS
 * @brief Macro to save additional registers in the stack frame.
 * 
 * This macro saves the registers s3, s4, s5, and s6 onto the stack. It is used
 * when more registers need to be preserved across function calls.
 */
.macro RISCV_ABI_SAVE_REGISTERS
    // Save additional registers
    addi sp, sp, -16
    sw s3, 0(sp)
    sw s4, 4(sp)
    sw s5, 8(sp)
    sw s6, 12(sp)
.endm   
/**
 * @macro RISCV_ABI_RESTORE_REGISTERS
 * @brief Macro to restore additional registers from the stack frame.
 * 
 * This macro restores the registers s3, s4, s5, and s6 from the stack. It is used
 * to clean up the stack frame after the function has completed its operations.
 */
.macro RISCV_ABI_RESTORE_REGISTERS
    // Restore additional registers
    lw s3, 0(sp)
    lw s4, 4(sp)
    lw s5, 8(sp)
    lw s6, 12(sp)
    addi sp, sp, 16
.endm
/**
 * @macro COMPUTE_SIGNATURE
 * @brief Macro to compute a signature based on the operation.
 * * This macro is a placeholder for actual signature computation logic.
 * * It could be a simple XOR of the operands or some other operation.
 * * The actual implementation will depend on the specific requirements of the signature computation.
 * * @note This macro is called verbosely at every operation in the sbst core.
 * * @return The computed signature in register t0.
 */
.macro COMPUTE_SIGNATURE // this could be a macro (called verbosily at every operation in the sbst core)
    // Compute the signature based on the operation
    // This is a placeholder for actual signature computation logic
    // For example, it could be a simple XOR of the operands or some other operation
    li t0, 0 // Initialize signature to zero
    // Perform operations and update signature
    // Example: t0 ^= a0 ^ a1; // where a0 and a1 are operands
    // The actual implementation will depend on the specific requirements of the signature computation
    // For now, we just return the signature in t0
    ret t0 // Return the computed signature in t0       
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
    // For example, it could compare the computed signature in t0 against a predefined value
    // The actual implementation will depend on the specific requirements of the signature checking
    // For now, we just return a dummy value indicating success
    li a0, 1 // Assume signature check passed (1 for success, 0 for failure)
    ret a0 // Return the result of the signature check in a0
    // The actual implementation will depend on the specific requirements of the signature checking
    // For now, we just return a dummy value indicating success
    // In a real implementation, you would compare the computed signature in t0 against a predefined value
    // and return 1 for success or 0 for failure.
    // Example: if (t0 == predefined_value) { a0 = 1; } else { a0 = 0; }
    // The actual implementation will depend on the specific requirements of the signature checking     
.endm 

#endif /* __RISCV_UTILS_H__ */