/**
  * GreenPois0n Cynanide - coprocessor.S
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

.global read_processor_id
.global read_processor_features
.global read_silicon_id
.global read_control_register
.global write_control_register
.global read_auxcontrol_register
.global write_auxcontrol_register
.global read_TBB0
.global write_TBB0
.global read_DAC
.global write_DAC
.global clear_icache
@ pod2g: removed, not armv6 compatible
@.global clear_dcache
@.global clear_cpu_caches

.code 32
read_processor_id:
	mrc p15, 0, r0, c0, c0, 0
	bx lr

read_processor_features:
	mrc p15, 0, r0, c0, c1, 0
	bx lr

read_silicon_id:
	mrc p15, 1, r0, c0, c0, 7
	bx lr

read_control_register:
	mrc p15, 0, r0, c1, c0, 0
	bx lr

write_control_register:
	mcr p15, 0, r0, c1, c0, 0
	bx lr

read_auxcontrol_register:
	mrc p15, 0, r0, c1, c0, 1
	bx lr

write_auxcontrol_register:
	mcr p15, 0, r0, c1, c0, 1
	bx lr

read_TBB0:
	mrc p15, 0, r0, c2, c0, 0
	bx lr

write_TBB0:
	mcr p15, 0, r0, c2, c0, 0
	bx lr

read_DAC:
	mrc p15, 0, r0, c3, c0, 0
	bx lr

write_DAC:
	mcr p15, 0, r0, c3, c0, 0
	bx lr

clear_icache:
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0  @ Invalidate I-Cache
    mcr p15, 0, r0, c7, c5, 4  @ Flush Prefetch Buffer
    nop
    nop
    nop
    nop
    bx lr

@ pod2g: removed, not armv6 compatible 
@clear_dcache:
@    mov r2, #0x2000
@
@outside:
@   sub r2, r2, #0x40
@   mov r1, #0
@
@inside:
@    subs r1, r1, #0x40000000
@    orr r0, r1, r2
@    mcr p15, 0, r0, c7, c10, 2
@    bne inside
@    cmp r2, #0
@    bne outside
@    mov r0, #0
@    mcr p15, 0, r0, c7, c10, 4
@    bx lr
@
@clear_cpu_caches:
@    bl clear_dcache
@    bl clear_icache
@    bx lr
