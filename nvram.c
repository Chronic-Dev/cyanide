/**
  * GreenPois0n Cynanide - nvram.c
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
#include <string.h>

#include "lock.h"
#include "nvram.h"
#include "common.h"

LinkedList* gNvramList = NULL;

void* find_nvram_list() {
	unsigned int ref1 = find_string(TARGET_BASEADDR, TARGET_BASEADDR, 0x40000, "build-style");
	unsigned int* ref2 = find_string(ref1+4, ref1+4, 0x40000, "build-style");
	ref2 -= 5;
	return *ref2;
}

int nvram_init() {
	gNvramList = find_nvram_list();
	if(gNvramList == NULL) {
		puts("Unable to find gNvramList\n");
	} else {
		printf("Found gNvramList at 0x%x\n", gNvramList);
		cmd_add("nvram", &nvram_cmd, "view and modify nvram variables");
	}
	return 0;
}

int nvram_cmd(int argc, CmdArg* argv) {
	char* var = NULL;
	char* value = NULL;
	char* action = NULL;
	if(argc < 2) {
		puts("usage: nvram <action> [options]\n");
		puts("  list              \t\tdisplay list of nvram variables\n");
		puts("  remove <var>      \t\tdeletes entry from nvram variables\n");
		puts("  get <var>         \t\tshow contents of nvram variable\n");
		puts("  set <var> <value> \t\tset contents of nvram variable\n\n");
		return 0;
	}

	action = argv[1].string;
	if(argc == 2) {
		if(!strcmp(action, "list")) {
			nvram_display_list();
			return 0;
		}

	} else if(argc == 3) {
		if(!strcmp(action, "get")) {
			var = argv[2].string;
			return nvram_get_var(var);

		} else if(!strcmp(action, "remove")) {
			var = argv[2].string;
			return nvram_remove_var(var);
		}

	} else if(argc == 4) {
		if(!strcmp(action, "set")) {
			var = argv[2].string;
			value = argv[3].string;
			return nvram_set_var(var, value);
		}
	}

	return 0;
}

void nvram_display_list() {
	NvramVar* var = (NvramVar*) gNvramList->next;
	enter_critical_section();
	while(var != (void*) gNvramList) {
		printf("0x%08x: %s = %s\n", var, var->name, var->string);
		var = var->next;
	}
	printf("\n");
	exit_critical_section();
}

int nvram_remove_var(const char* name) {
	NvramVar* var = nvram_find_var(name);
	if(var == NULL) {
		return -1;
	}

	NvramVar* next = var->next;
	NvramVar* prev = var->prev;

	next->prev = prev;
	prev->next = next;

	var->next = 0;
	var->prev = 0;

	free(var->string);
	free(var);

	return 0;
}

NvramVar* nvram_find_var(const char* name) {
	NvramVar* var = (NvramVar*) gNvramList->next;
	while(var != (void*) gNvramList) {
		if(!strcmp(name, var->name)) {
			return var;
		}
		var = (NvramVar*) var->next;
	}
	return NULL;
}

int nvram_get_var(const char* name) {
	enter_critical_section();
	NvramVar* var = nvram_find_var(name);
	if(var == NULL) {
		puts("unable to find nvram entry\n\n");
		exit_critical_section();
		return -1;
	}

	printf("%s = %s\n", var->name, var->string);
	exit_critical_section();

	return 0;
}

int nvram_set_var(const char* name, const char* value) {
	enter_critical_section();
	NvramVar* var = NULL;
	var = nvram_find_var(name);
	if(var != NULL) {
		nvram_remove_var(name);
		var = NULL;
	}
	NvramVar* next = (NvramVar*) gNvramList;
	NvramVar* prev = (NvramVar*) gNvramList->prev;

	var = malloc(sizeof(NvramVar));
	if(var == NULL) {
		exit_critical_section();
		return -1;
	}

	strncpy(var->name, name, 0x40);
	var->string = malloc(0x200);
	if(var->string == NULL) {
		free(var);
		exit_critical_section();
		return -1;
	}
	
	strncpy(var->string, value, 0x200);
	var->integer = strtoul(var->string, NULL, 0);
	var->save = 1;

	var->next = next;
	var->prev = prev;

	next->prev = var;
	prev->next = var;

	exit_critical_section();
	return 0;
}
