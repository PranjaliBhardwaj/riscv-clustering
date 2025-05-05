# for risc-v optimisation routines

.section .text
.global riscv_euclidean_distance
.global riscv_start_counters
.global riscv_stop_counters
# a0 = a, a1 = b, a2 = dim
riscv_euclidean_distance:
    
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    
    mv s0, a2             
    fmv.d.x ft0, zero      
    
    
1:
    beqz s0, 3f            
    
    
    fld ft1, 0(a0)
    fld ft2, 0(a1)
    
    
    fsub.d ft3, ft1, ft2
    fmul.d ft3, ft3, ft3
    fadd.d ft0, ft0, ft3
    
    
    addi a0, a0, 8
    addi a1, a1, 8
    addi s0, s0, -1
    j 1b
    
3:
    
    fsqrt.d fa0, ft0
    
    # Epilogue
    ld s0, 0(sp)
    ld ra, 8(sp)
    addi sp, sp, 16
    ret


riscv_start_counters:
    
    li t0, 1
    csrw mcountinhibit, zero  
    csrw mcycle, zero         
    csrw minstret, zero       
    ret

riscv_stop_counters:
    
    csrr t0, mcycle
    la t1, cycle_count
    sd t0, 0(t1)
    
    csrr t0, minstret
    la t1, inst_count
    sd t0, 0(t1)
    
   
    li t0, 1
    csrw mcountinhibit, t0
    ret

.section .data
cycle_count: .dword 0
inst_count: .dword 0
