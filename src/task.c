/*
 *
 *  greenpois0n - task.c
 *  (c) 2009 Chronic-Dev Team
 *
 */

#include <stdio.h>

#include "task.h"
#include "lock.h"
#include "common.h"

LinkedList* gTaskList = SELF_TASK_LIST;
TaskDescriptor** gTaskRunning = SELF_TASK_RUNNING;
//unsigned int* gTaskCount = SELF_TASK_COUNT;
void(*task_yield)(void) = SELF_TASK_YIELD;

void task_display_list() {
	LinkedList* list = gTaskList->next;

	puts("Tasks:\n");
	while(list != gTaskList) {
		TaskDescriptor* task = (void*) list - 4;

		enter_critical_section();
		printf("  (0x%08x) %s", task, task->taskName);
		if(task == *gTaskRunning) printf("*");
		printf("\n");
		exit_critical_section();

		list = list->next;
	}
	puts("\n");
}

TaskDescriptor* task_find(const char* name) {
	LinkedList* list = gTaskList->next;
	while(list != gTaskList) {
		TaskDescriptor* task = (void*) list - 4;
		if(!strcmp(task->taskName, name)) {
			return task;
		}
		list = list->next;
	}
	return NULL;
}

int task_display_info(const char* name) {
	TaskDescriptor* task = task_find(name);
	if(task == NULL) {
		puts("Cannot find task\n");
		return -1;
	}

	enter_critical_section();
	printf("Found %s\n", task->taskName);
	printf("  identifier1 = 0x%08x\n", task->identifier1);
	printf("  taskList.prev = 0x%08x\n", task->taskList.prev);
	printf("  taskList.next = 0x%08x\n", task->taskList.next);
	printf("  runqueueList.prev = 0x%08x\n", task->runqueueList.prev);
	printf("  runqueueList.next = 0x%08x\n", task->runqueueList.next);
	printf("  state = %d\n", task->state);
	printf("  criticalSectionNestCount = %d\n", task->criticalSectionNestCount);
	printf("  registers.r4 = 0x%08x\n", task->savedRegisters.r4);
	printf("  registers.r5 = 0x%08x\n", task->savedRegisters.r5);
	printf("  registers.r6 = 0x%08x\n", task->savedRegisters.r6);
	printf("  registers.r7 = 0x%08x\n", task->savedRegisters.r7);
	printf("  registers.r8 = 0x%08x\n", task->savedRegisters.r8);
	printf("  registers.r9 = 0x%08x\n", task->savedRegisters.r9);
	printf("  registers.r10 = 0x%08x\n", task->savedRegisters.r10);
	printf("  registers.r11 = 0x%08x\n", task->savedRegisters.r11);
	printf("  registers.sp = 0x%08x\n", task->savedRegisters.sp);
	printf("  registers.lr = 0x%08x\n", task->savedRegisters.lr);
	printf("  exitState = 0x%08x\n", task->exitState);
	printf("  taskRoutine = 0x%08x\n", task->taskRoutine);
	printf("  unknown_passed_value = 0x%08x\n", task->unknown_passed_value);
	printf("  storage = 0x%x\n", task->storage);
	printf("  storageSize = 0x%08x\n", task->storageSize);
	printf("  taskName = %s\n", task->taskName);
	printf("  identifier2 = 0x%08x\n", task->identifier2);
	exit_critical_section();
}

void task_add_queue(TaskDescriptor* task) {
	//*gTaskCount++;
}

void task_start(TaskDescriptor* task) {
#ifdef S5L8922X
	void(*_task_setup)(TaskDescriptor *task, const char *name, void *handler, int exit, void *stack, unsigned int stack_size) = (void*) 0x4FF18F75;
	void(*_task_start)(TaskDescriptor*) = (void*) 0x4FF18F55;
	_task_setup(task, task->taskName, task->taskRoutine, task->exitState, task->storage, task->storageSize);
	_task_start(task);
#else
	if(task->state == 0) {
		task->state = TASK_READY;
		enter_critical_section();
		task_add_queue(task);
		exit_critical_section();
	}
#endif
}

void task_exit(TaskDescriptor* task) {
#ifdef S5L8922X
	void(*_task_exit)(void) = (void*) 0x4FF19470;
	*gTaskRunning = task;
	_task_exit();
#else
	printf("Error not implemented\n");
#endif
}
