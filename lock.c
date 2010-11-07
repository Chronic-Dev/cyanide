/**
  * GreenPois0n Cynanide - lock.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "lock.h"
#include "common.h"

void enter_critical_section() {
	return;
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->criticalSectionNestCount < 0
			|| current_task->criticalSectionNestCount > 1000) {
		panic("enter_critical_section: error\n");
	}

	current_task->criticalSectionNestCount++;
	if(current_task->criticalSectionNestCount == 1) {
		disable_irq();
	}
}

void exit_critical_section() {
	return;
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->criticalSectionNestCount < 0
			|| current_task->criticalSectionNestCount > 1000) {
		panic("exit_critical_section: error\n");
	}

	current_task->criticalSectionNestCount--;
	if(current_task->criticalSectionNestCount == 0) {
		enable_irq();
	}
}

void enable_irq() {
	__asm__("mrs r0, cpsr");
	__asm__("bic r1, r0, #0x80");
	__asm__("msr cpsr_c, r1");
	__asm__("and r0, r0, #0x80");
}

void disable_irq() {
	__asm__("mrs r0, cpsr");
	__asm__("orr r1, r0, #0x80");
	__asm__("msr cpsr_c, R1");
	__asm__("and r0, r0, #0x80");
}
