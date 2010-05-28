/*
 *
 *  greenpois0n - payload/src/lock.c
 *  (c) 2010 Chronic-Dev Team
 *
 */

#include "task.h"
#include "lock.h"
#include "common.h"

void enter_critical_section() {
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->criticalSectionNestCount < 0
			&& current_task->criticalSectionNestCount > 1000) {
		printf("enter_critical_section: error\n");
		halt();
	}

	current_task->criticalSectionNestCount++;
	if(current_task->criticalSectionNestCount == 1) {
		disable_irq();
	}
}

void exit_critical_section() {
	TaskDescriptor* current_task = *gTaskRunning;
	if(current_task->criticalSectionNestCount < 0
			&& current_task->criticalSectionNestCount > 1000) {
		printf("exit_critical_section: error\n");
		halt();
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
