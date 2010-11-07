/**
  * GreenPois0n Cynanide - uart.c
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

#include <stdlib.h>
#include <string.h>

#include "uart.h"
#include "task.h"
#include "common.h"
#include "commands.h"
#include "functions.h"

void(*uart_write)(int bus, char* buffer, int size) = NULL;
void(*uart_read)(int bus, char* buffer, int size1, int size2) = NULL;

void* find_uart_read() {
	return find_function("uart_read", TARGET_BASEADDR, TARGET_BASEADDR);
}

void* find_uart_write() {
	return find_function("uart_write", TARGET_BASEADDR, TARGET_BASEADDR);
}

int uart_init() {
	uart_read = find_uart_read();
	if(uart_read == NULL) {
		puts("Unable to find uart_read\n");
	} else {
		printf("Found uart_read at 0x%x\n", uart_read);
	}

	uart_write = find_uart_write();
	if(uart_write == NULL) {
		puts("Unable to find uart_write\n");
	} else {
		printf("Found uart_write at 0x%x\n", uart_write);
	}

	if(uart_read && uart_write) {
		cmd_add("uart", &uart_cmd, "read and write data to serial interfaces");
	}

	return 0;
}

int uart_cmd(int argc, CmdArg* argv) {
	int i = 0;
	int bus = 0;
	char* action = NULL;
	unsigned char* data = NULL;
	if(argc < 2) {
		puts("usage: uart <read/write> [options]\n");
		puts("  read <bus>         \t\tdisplay list of active tasks\n");
		puts("  write <bus> <data> \t\tdisplay info about task\n");
		return 0;
	}

	bus = argv[2].uinteger;
	action = argv[1].string;
	if(!strcmp(action, "read")) {
		TaskDescriptor* uart_reader_task = task_create("bb_reader", &uart_reader, 0, 0x200);
		task_start(uart_reader_task);

	} else
	if(!strcmp(action, "write")) {
		data = malloc(0x100);
		memset(data, 0, 0x100);
		for(i = 3; i < argc; i++) {
			if(i > 2) {
				strncat(data, " ", 0x100);
			}
			strncat(data, argv[i].string, 0x100);
		}
		strncat(data, "\r\n", 0x100);
		uart_write(bus, data, strlen(data));
	}

	free(data);

	return 0;
}

void uart_reader(void* arg) {
	char byte;
	while(1) {
		uart_read(1, &byte, 1, 1);
		printf("%c", byte);
	}
}
