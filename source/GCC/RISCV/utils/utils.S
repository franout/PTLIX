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

.macro RISCV_ABI_PROLOGUE
    // Save the registers and stack pointer
    addi sp, sp, -16
    sw s2, 0(sp)
    sw s1, 4(sp)
    sw s0, 8(sp)
    sw ra, 12(sp)
    
.endm


.macro COMPUTE_SIGNATURE // this could be a macro (called verbosily at every operation in the sbst core)
    
.endm


.macro CHECK_SIGNATURE 
    
.endm 
