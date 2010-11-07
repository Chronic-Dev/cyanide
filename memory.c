/**
  * GreenPois0n Cynanide - memory.c
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

#include "lock.h"
#include "memory.h"
#include "common.h"
#include "commands.h"

int memory_init() {
	//printf("Initializing memory\n");
	cmd_add("memory", &memory_cmd, "display, search, and manipulate memory");
	return 0;
}

int memory_cmd(int argc, CmdArg* argv) {
	char* bytes = NULL;
	char* action = NULL;
	char* source = NULL;
	char* destination = NULL;
	unsigned int size = 0;

	if(argc < 4) {
		puts("usage: memory <search/dump/copy> [options]\n");
		puts("  search <address> <size> <bytes>\tfind address of specified byte sequence\n");
		puts("  dump <address> <size>          \tdump memory from address over usb\n");
		puts("  copy <from> <to> <size>        \tcopy memory from one address to another\n");
		puts("  move <from> <to> <size>        \tmove memory from one address to another\n");
		return 0;
	}

	action = argv[1].string;
	if(argc == 5) {
		if(!strcmp(action, "search")) {
			bytes = argv[4].string;
			size = argv[3].uinteger;
			source = (void*) argv[2].uinteger;
			return memory_search(source, size, bytes);
		}
	}

	if(argc == 4) {
		if(!strcmp(action, "dump")) {
			printf("Not implemented yet\n");
			return 0;
		}
	}

	if(argc == 5) {
		if(!strcmp(action, "copy")) {
			size = argv[4].uinteger;
			source = (char*) argv[2].uinteger;
			destination = (char*) argv[3].uinteger;
			return memcpy(destination, source, size);
		}
	}

	if(argc == 5) {
		if(!strcmp(action, "move")) {
			size = argv[4].uinteger;
			source = (char*) argv[2].uinteger;
			destination = (char*) argv[3].uinteger;
			return memmove(destination, source, size);
		}
	}

	return 0;
}

int memory_search(char* source, unsigned int size, char* bytes) {
	int i = 0;
	char buffer[64];
	unsigned int byte = 0;

	int length = strlen(bytes) / 2;
	if(length <= 0 || length >= 64) {
		printf("byte sequence is too long\n");
		return -1;
	}

	memset(buffer, '\0', 64);
	for(i = 0; i < length; i++) {
		sscanf(bytes, "%02x", &byte);
		buffer[i] = byte;
		bytes += 2;
	}

	for(i = 0; i < size; i++) {
		if(!memcmp(&source[i], buffer, length)) {
			printf("Found byte sequence at 0x%x\n", &source[i]);
			return (int) &source[i];
		}
	}

	printf("unable to find byte sequence\n");
	return -1;
}
