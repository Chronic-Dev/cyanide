/**
  * GreenPois0n Cynanide - task.c
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
#include "commands.h"
#include "functions.h"

LinkedList* gTaskList = SELF_TASK_LIST;
TaskDescriptor** gTaskRunning = SELF_TASK_RUNNING;
void(*task_yield)(void) = NULL;
void(*task_start)(TaskDescriptor* task) = NULL;
TaskDescriptor*(*task_create)(char* name, Task task, void* arg, unsigned int stack) = NULL;

void* find_task_yield() {
	return find_function("task_yield", TARGET_BASEADDR, TARGET_BASEADDR);
}

void* find_task_running() {
	return 0;
}

void* find_task_list() {
	return 0;
}

void* find_task_create() {
	return find_function("task_create", TARGET_BASEADDR, TARGET_BASEADDR);
}

void* find_task_exit() {
	return find_function("task_exit", TARGET_BASEADDR, TARGET_BASEADDR);
}

void* find_task_start() {
	unsigned int x = patch_find(TARGET_BASEADDR, 0x40000, "\x90\xB5\x01\xAF\x43\x69\x04\x46", 8);
	return x+1;
}

int task_init() {
	task_yield = find_task_yield();
	if(task_yield == NULL) {
		puts("Unable to find task_yield\n");
	} else {
		printf("Found task_yield at 0x%x\n", task_yield);
	}

	//gTaskRunning = find_task_running();
	if(gTaskRunning == NULL) {
		puts("Unable to find gTaskRunning\n");
	} else {
		printf("Found gTaskRunning at 0x%x\n", gTaskRunning);
	}

	//gTaskList = find_task_list();
	if(gTaskList == NULL) {
		puts("Unable to find gTaskList\n");
	} else {
		printf("Found gTaskList at 0x%x\n", gTaskList);
	}

	task_create = find_task_create();
	if(task_create == NULL) {
		puts("Unable to find task_create\n");
	} else {
		printf("Found task_create at 0x%x\n", task_create);
	}

	task_start = find_task_start();
	if(task_start == NULL) {
		puts("Unable to find task_start\n");
	} else {
		printf("Found task_start at 0x%x\n", task_start);
	}

	if(task_yield && gTaskRunning && gTaskList) {
		cmd_add("task", &task_cmd, "view and change running tasks");
	}

	return 0;
}

int task_cmd(int argc, CmdArg* argv) {
	int i = 0;
	char* name = NULL;
	char* action = NULL;
	if(argc < 2) {
		puts("usage: task <action> [options]\n");
		puts("  list          \t\tdisplay list of active tasks\n");
		puts("  info <task>   \t\tdisplay info about task\n");
		puts("  create <name> <function>  \t\tcreate a new task with name");
		puts("  start <task>  \t\tstart a existing task\n");
		return 0;
	}

	action = argv[1].string;
	if(!strcmp(action, "list")) {
		task_display_list();
	}

	if(argc >= 3) {
		name = malloc(0x10);
		memset(name, 0, 0x10);
		if(!strcmp(action, "info")) {
			for(i = 2; i < argc; i++) {
				if(i > 2) {
					strncat(name, " ", 0x10);
				}
				strncat(name, argv[i].string, 0x10);
			}

			task_display_info(name);
		} else

		if(!strcmp(action, "start")) {
			for(i = 2; i < argc; i++) {
				if(i > 2) {
					strncat(name, " ", 0x10);
				}
				strncat(name, argv[i].string, 0x10);
			}

			TaskDescriptor* task = task_find(name);
			if(task != NULL) {
				task_start(task);
			} else {
				puts("Cannot find task\n");
			}
		} else

		if(!strcmp(action, "exit")) {
			for(i = 2; i < argc; i++) {
				if(i > 2) {
					strncat(name, " ", 0x10);
				}
				strncat(name, argv[i].string, 0x10);
			}

			TaskDescriptor* task = task_find(name);
			if(task != NULL) {
				task_exit(task);
			} else {
				puts("Cannot find task\n");
			}
		}

		free(name);
	}

	return 0;
}

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

/*
void task_add_queue(TaskDescriptor* task) {
	printf("task_add_queue: Not implemented\n");
}

void task_start(TaskDescriptor* task) {
	printf("task_start: Not implemented\n");
	if(task->state == 0) {
		task->state = TASK_READY;
		enter_critical_section();
		task_add_queue(task);
		exit_critical_section();
	}
}
*/
void task_exit(TaskDescriptor* task) {
	printf("task_exit: Not implemented\n");
}

