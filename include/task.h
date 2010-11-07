/**
  * GreenPois0n Cynanide - task.h
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

#ifndef TASK_H
#define TASK_H

#include "common.h"
#include "device.h"
#include "offsets.h"
#include "commands.h"

#ifdef TARGET_TASK_RUNNING
#	define SELF_TASK_RUNNING ((TaskDescriptor**)(TARGET_BASEADDR + TARGET_TASK_RUNNING))
#endif
#ifdef TARGET_TASK_LIST
#	define SELF_TASK_LIST ((LinkedList*)(TARGET_BASEADDR + TARGET_TASK_LIST))
#endif

#ifndef SELF_TASK_RUNNING
#	define SELF_TASK_RUNNING 0
#	error "SELF_TASK_RUNNING not defined"
#endif

#ifndef SELF_TASK_LIST
#	define SELF_TASK_LIST 0
#	error "SELF_TASK_LIST not defined"
#endif

#define TaskDescriptorIdentifier1 0x7461736b // 'task'
#define TaskDescriptorIdentifier2 0x74736b32 // 'tsk2'

typedef struct Event Event;

typedef void (*TaskRoutineFunction)(void* opaque);
typedef void (*EventHandler)(Event* event, void* opaque);

typedef struct TaskRegisterState {
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int sp;
	unsigned int lr;
} TaskRegisterState;

typedef enum TaskState {
	TASK_READY = 1,
	TASK_RUNNING = 2,
	TASK_IDLE = 3,
	TASK_SLEEPING = 4,
	TASK_STOPPED = 5
} TaskState;

struct Event {
	LinkedList list;
	unsigned long long deadline;
	unsigned long long interval;
	EventHandler handler;
	void* opaque;
};

typedef struct TaskDescriptor {
	unsigned int identifier1;
	LinkedList taskList;
	LinkedList runqueueList;
	TaskState state;
	unsigned int criticalSectionNestCount;
	TaskRegisterState savedRegisters;
	Event sleepEvent;
	LinkedList linked_list_3;
	unsigned int exitState;
	TaskRoutineFunction	taskRoutine;
	void* unknown_passed_value;
	void* storage;
	unsigned int storageSize;
	char taskName[16];
	unsigned int identifier2;
} TaskDescriptor;

typedef void(*Task)(void* arg);

extern LinkedList* gTaskList;
extern TaskDescriptor** gTaskRunning;
//extern unsigned int* gTaskCount;
extern void(*task_yield)(void);
extern TaskDescriptor*(*task_create)(char* name, Task task, void* arg, unsigned int stack);
extern void(*task_start)(TaskDescriptor* task);

int task_init();
int task_cmd(int argc, CmdArg* argv);
void task_display_list();
TaskDescriptor* task_find(const char* name);
int task_display_info(const char* name);
//void task_start(TaskDescriptor* task);
//void task_exit(TaskDescriptor* task);

#endif /* TASK_H */
