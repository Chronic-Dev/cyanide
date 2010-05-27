/*
 *
 *  greenpois0n - payload/src/entry.s
 *  (c) 2010 Chronic-Dev Team
 *
 */

.arm
.ltorg
.code 32
_start:
.global _start
	b		reset
	ldr		pc, undefined_vector
	ldr		pc, syscall_vector
	ldr		pc, prefetch_abort_vector
	ldr		pc, data_abort_vector
	ldr		pc, reserved_vector
	ldr		pc, irq_vector
	ldr		pc, fiq_vector

reset_vector:            .word reset
undefined_vector:        .word halt
syscall_vector:          .word halt
prefetch_abort_vector:   .word halt
data_abort_vector:       .word halt
reserved_vector:         .word halt
irq_vector:              .word halt
fiq_vector:              .word halt

.code 32
reset:
    stmfd  sp!, {r4-r12,lr}
	bl     main
    ldmfd  sp!, {r4-r12,pc}

halt:
    b      halt
