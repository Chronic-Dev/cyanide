/**
  * GreenPois0n Cynanide - breakpoint.c
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Cyril Cattiaux
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
#include <string.h>

#include "lock.h"
#include "common.h"
#include "commands.h"
#include "breakpoint.h"
#include "coprocessor.h"

/*
 * Public Functions
 */

BreakpointEntry* breakpoint_root = NULL;

BreakpointLog* breakpoint_logs = NULL;

int break_init() {
	cmd_add("break", &break_cmd, "create and delete debugging breakpoints");
	return 0;
}

int break_cmd(int argc, CmdArg* argv) {
	char* action = NULL;
	unsigned int value = 0;
	if(argc < 2) {
		enter_critical_section();
		puts("usage: break <list/add/remove> [options]\n");
		puts("  list          \t\tdisplay list of active breakpoints\n");
		puts("  add <address> [<hexdump addr> <hexdump len>]\t\tadd new active breakpoint\n");
		puts("  remove <id>   \t\tremove active breakpoint\n");
		puts("  log <show/clear>\n");
		puts("    show        \t\tdisplay log of hit breakpoints\n");
		puts("    show <id>   \t\tdisplay a full breakpoint trace\n");
		puts("    clear       \t\tclears the log\n");
		puts("\n");
		exit_critical_section();
		return 0;
	}

	action = argv[1].string;
	if(!strcmp(action, "list")) {
		if (argc != 2) {
			printf("[!] 'list' don't need any argument. Read usage.\n", action);
			return -1;
		}
		breakpoint_list();
		return 0;
	} else if(!strcmp(action, "add")) {
		if (argc != 3 && argc != 5) {
			printf("[!] 'log add' needs either 1 or 3 arguments. Read usage.\n");
			return -1;
		}

		if (argv[2].type!=CMDARG_TYPE_INTEGER) {
			puts("[!] <address> must be an integer !\n");
			return -1;
		}
		value = argv[2].uinteger;
		BreakpointEntry* bp = breakpoint_add((void *) value, FALSE);
		if (bp != NULL) {
                       	enter_critical_section();
                       	printf("New breakpoint at 0x%08x with id %d\n", bp->address, bp->id);
			if (argc == 5) {
				bp->hexdump_address = (void *) argv[3].uinteger;
				bp->hexdump_len = argv[4].uinteger;
				printf("The breakpoint will trigger a hexdump of address:0x%08x len:0x%08x.\n", bp->hexdump_address, bp->hexdump_len);
			}
                       	exit_critical_section();
			return 0;
		} else {
                       	enter_critical_section();
                       	printf("[!] Failed to add breakpoint at %0x%08x.\n", value);
                       	exit_critical_section();
			return -1;
		}
	} else if(!strcmp(action, "remove")) {
		if (argc != 3) {
			printf("[!] 'remove' needs 1 argument: the id of the breakpoint.\n", action);
			return -1;
		}

		value = argv[2].uinteger;
		if (breakpoint_remove(value)) {
			enter_critical_section();
			printf("Removed breakpoint %d.\n", value);
			exit_critical_section();
			return 0;
		} else {
			enter_critical_section();
			printf("[!] Breakpoint %d not found.\n", value);
			exit_critical_section();
			return -1;
		}
	} else if (!strcmp(action, "log")) {
		if (argc < 3 || argv[2].type!=CMDARG_TYPE_STRING) {
			printf("[!] 'log' sub-action missing. Read command usage.\n");
			return -1;
		}
		char* subaction = argv[2].string;
		if (!strcmp(subaction, "show")) {
			if (argc == 4) {
				breakpoint_log_show(argv[3].uinteger);
			} else if (argc == 3) {
				breakpoint_log_list();
			} else {
				printf("[!] 'log clear' takes either 0 or 1 argument. Read usage.\n", action);
				return -1;
			}
			return 0;
		} else if (!strcmp(subaction, "clear")) {
			if (argc != 3) {
				printf("[!] 'log clear' don't need any argument. Read usage.\n", action);
				return -1;
			}
			breakpoint_log_clear();
			printf("Log cleared.\n");
			return 0;
		} else {
			printf("[!] Unknwon 'log' sub-action %s. Read command usage.\n", subaction);
			return -1;
		}
	} else {
		enter_critical_section();
		printf("[!] Unknown command <%s>.\n", action);
		exit_critical_section();
		return -1;
	}

	return 0;
}

void breakpoint_log_list() {
	BreakpointLog *bl = breakpoint_logs;
	enter_critical_section();
	if (bl==NULL) {
		printf("The log is empty.\n");
	} else {
		printf("Breakpoint log :\n");
		while (bl!=NULL) {
			printf("#%04d id:%04d pc=0x%08x\n", bl->id, bl->bp_id, bl->pc);
			bl = bl->next;
		}
	}
	exit_critical_section();
}

void breakpoint_log_show(unsigned int id) {
	BreakpointLog *bl = breakpoint_log_find(id);
	enter_critical_section();
	if (bl==NULL) {
		printf("[!] Can't find the log entry of id %d\n", id);
	} else {
		printf("Breakpoint log entry #%d:\n", bl->id);
		printf("\nBreakpoint %d hit at 0x%08x\n", bl->bp_id, bl->pc);
		printf(" r0:  0x%08x  r1:  0x%08x  r2:  0x%08x  r3:   0x%08x\n", bl->r0, bl->r1, bl->r2, bl->r3);
		printf(" r4:  0x%08x  r5:  0x%08x  r6:  0x%08x  r7:   0x%08x\n", bl->r4, bl->r5, bl->r6, bl->r7);
		printf(" r8:  0x%08x  r9:  0x%08x  r10: 0x%08x  r11:  0x%08x\n", bl->r8, bl->r9, bl->r10, bl->r11);
		printf(" r12: 0x%08x  sp:  0x%08x  lr:  0x%08x  spsr: 0x%08x\n", bl->r12, bl->sp, bl->lr, bl->spsr);

		printf("\nStack Dump:\n");
		int sp = bl->sp;
		int i;
		for(i = 0; i < 0x10; i += 4) {
			printf("0x%08x:  0x%08x  0x%08x  0x%08x  0x%08x\n", sp, bl->stack[i], bl->stack[i+1], bl->stack[i+2], bl->stack[i+3]);
			sp += 0x10;
		}
	
		if (bl->hexdump_result!=NULL) {	
			printf("\nMemory Dump of 0x%08x:\n", bl->hexdump_address);
			hexdump((unsigned char*) bl->hexdump_result, bl->hexdump_len);
		}

		printf("\n");
	}
	exit_critical_section();
}

void breakpoint_log_clear() {
	BreakpointLog *bl = breakpoint_logs;
	while (bl!=NULL) {
		BreakpointLog *tmp = bl;
		bl = bl->next;
		if (tmp->hexdump_result!=NULL) free(tmp->hexdump_result);
		free(tmp);
	}
	breakpoint_logs = NULL;
}

BreakpointLog* breakpoint_log_find(unsigned int id) {
	BreakpointLog *bl = breakpoint_logs;
	while (bl!=NULL) {
		if (bl->id==id) {
			return bl;
		}
		bl = bl->next;
	}
	return NULL;
}

void breakpoint_log_add(BreakpointLog *log) {
	if (breakpoint_logs==NULL) {
		log->id = 0;
		log->next = NULL;
		breakpoint_logs = log;
	} else {
		// seek to last element
		BreakpointLog *bl = breakpoint_logs;
		int id = 0;
		while (bl->next!=NULL) {
			id = bl->id + 1; 
			bl = bl->next;
		}
		if (bl!=NULL) id = bl->id +1;
		log->id = id;
		log->next = NULL;
		bl->next = log;
	}
}

BreakpointLog* breakpoint_log_remove(unsigned int id) {
	BreakpointLog *prev = breakpoint_logs;
	BreakpointLog *bl = breakpoint_logs;
	while (bl!=NULL) {
		if (bl->id==id) {
			prev->next = bl->next;
			return bl;
		}
		prev = bl;
		bl = bl->next;
	}
	return NULL;
}

void breakpoint_list() {
	enter_critical_section();

	BreakpointEntry* bp = breakpoint_root;
	if(bp == NULL) {
		printf("No active breakpoints\n");
	} else {
		printf("Breakpoints:\n");
		while(bp != NULL) {
			if(*((unsigned int*)bp->address) == bp->value) {
				*((volatile unsigned short*)bp->address) = BKPT_THUMB;
			}
			printf("  [%d] 0x%08x reset:%s hexdump:0x%08x-0x%08x\n", bp->id, bp->address,
					bp->reset ? "true" : "false", bp->hexdump_address, bp->hexdump_len);

			bp = bp->next;
		}
		printf("\n");
	}

	exit_critical_section();
}

BreakpointEntry* breakpoint_add(void* address, Bool reset) {
	BreakpointEntry* bp = breakpoint_root;
	if(bp != NULL) {
		while(bp != NULL) {
			if(*((unsigned int*)bp->address) == bp->value) {
				*((volatile unsigned short*)bp->address) = BKPT_THUMB;
			}

			if(bp->next == NULL) {
				BreakpointEntry* new_bp = malloc(sizeof(BreakpointEntry));
				new_bp->id = bp->id + 1;
				new_bp->reset = reset;
				new_bp->value = *((unsigned int*)address);
				new_bp->address = (void*)address;
				new_bp->next = NULL;
				new_bp->hexdump_address = NULL;
				new_bp->hexdump_len = 0;
				bp->next = new_bp;

				*((volatile unsigned short*)address) = BKPT_THUMB;
				clear_icache();
				//clear_dcache();

				return new_bp;
			}
			bp = bp->next;
		}

	} else {
		// no breakpoints exist yet, create breakpoint_root
		breakpoint_root = malloc(sizeof(BreakpointEntry));
		breakpoint_root->id = 0;
		breakpoint_root->reset = reset;
		breakpoint_root->value = *((unsigned int*)address);
		breakpoint_root->address = (void*)address;
		breakpoint_root->next = NULL;
		breakpoint_root->hexdump_address = NULL;
		breakpoint_root->hexdump_len = 0;

		*((volatile unsigned short*)address) = BKPT_THUMB;
		clear_icache();
		//clear_dcache();

		return breakpoint_root;
	}

	return NULL;
}

Bool breakpoint_remove(unsigned int id) {
	BreakpointEntry* prev = NULL;
	BreakpointEntry* bp = breakpoint_root;
	while(bp != NULL) {
		if(bp->id == id) {
			if(prev == NULL) {
				breakpoint_root = bp->next;
			} else {
				prev->next = bp->next;
			}
			*((volatile unsigned int*)bp->address) = bp->value;
			clear_icache();
			//clear_dcache();
			
			//free(bp);
			return TRUE;
		}
		prev = bp;
		bp = bp->next;
	}

	return FALSE;
}

/*
 * Private Functions
 */
void breakpoint(unsigned int* stack) {
	BreakpointEntry* bp = breakpoint_root;

	unsigned int r[13];
	unsigned int *sp = (unsigned int*) stack[0];
	unsigned int lr = stack[1];
	unsigned int spsr = stack[2];
	unsigned int pc = stack[16];
	unsigned int i = 0;
	for(i = 0; i <= 12; i++) {
		r[i] = stack[i+3];
	}
	
	unsigned int id = 0;
	void* hexdump_address = NULL;
	unsigned int hexdump_len = 0;
	while(bp != NULL) {
		if(bp->address == (void*) pc) {
			if(bp->reset) {
				// reset our original breakpoint and remove our reset breakpoint
				hexdump_address = bp->hexdump_address;
				hexdump_len = bp->hexdump_len;
				if (breakpoint_remove(bp->id)) {
					BreakpointEntry *bp_copy = breakpoint_add(bp->address - 2, FALSE);
					bp_copy->hexdump_address = hexdump_address;
					bp_copy->hexdump_len = hexdump_len;
				}
				return;
			}

			// add the reset breakpoint and remove the original
			id = bp->id;
			hexdump_address = bp->hexdump_address;
			hexdump_len = bp->hexdump_len;
			if (breakpoint_remove(bp->id)) {
				BreakpointEntry *bp_reset = breakpoint_add(bp->address + 2, TRUE);
				bp_reset->hexdump_address = hexdump_address;
				bp_reset->hexdump_len = hexdump_len;
			}
			
			break;
		}
		bp = bp->next;
	}

	BreakpointLog *bl = malloc(sizeof(BreakpointLog));
	bl->r0 = r[0];
	bl->r1 = r[1];
	bl->r2 = r[2];
	bl->r3 = r[3];
	bl->r4 = r[4];
	bl->r5 = r[5];
	bl->r6 = r[6];
	bl->r7 = r[7];
	bl->r8 = r[8];
	bl->r9 = r[9];
	bl->r10 = r[10];
	bl->r11 = r[11];
	bl->r12 = r[12];
	bl->sp = (unsigned int) sp;
	bl->lr = lr;
	bl->spsr = spsr;
	bl->pc = pc;
	bl->bp_id = id;
	for(i = 0; i < 0x10; i++) {
		bl->stack[i] = sp[i];
	}
	if (hexdump_len > 0) {
		unsigned char* buf = (unsigned char*) malloc(hexdump_len);
		memcpy(buf, hexdump_address, hexdump_len);
		bl->hexdump_address = hexdump_address;
		bl->hexdump_len = hexdump_len;
		bl->hexdump_result = (void*) buf;
	} else {
		bl->hexdump_address = NULL;
		bl->hexdump_len = 0;
		bl->hexdump_result = NULL;
	}
	breakpoint_log_add(bl);
	breakpoint_log_show(bl->id);
}
