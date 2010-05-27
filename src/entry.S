/**
  * GreenPois0n Cynanide - entry.s
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

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

reset_vector:.word reset
undefined_vector:.word halt
syscall_vector:  .word halt
prefetch_abort_vector:   .word halt
data_abort_vector:   .word halt
reserved_vector: .word halt
irq_vector:  .word halt
fiq_vector:  .word halt

.code 32
reset:
stmfd  sp!, {r4-r12,lr}
	bl main
ldmfd  sp!, {r4-r12,pc}

halt:
b  halt
