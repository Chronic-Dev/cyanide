/**
  * GreenPois0n Cynanide - radio.c
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

#include "uart.h"
#include "radio.h"
#include "commands.h"

static Bool gRadioReadInit = FALSE;

int radio_init() {
	srand(1);
	if(uart_read && uart_write) {
		cmd_add("radio", &radio_cmd, "send AT commands to baseband radio");
	}
	return 0;
}

int radio_cmd(int argc, CmdArg* argv) {
	int i = 0;
	int ret = 0;
	char* data = NULL;

	if(gRadioReadInit == FALSE) {
		//TaskDescriptor* radio_reader_task = task_create("radio_reader", &radio_reader, 0, 0x2000);
		//task_start(radio_reader_task);
		gRadioReadInit = TRUE;
	}

	if(argc == 1) {
		radio_send_random();
		return 0;
	}

	data = malloc(0x100);
	memset(data, '\0', 0x100);
	for(i = 1; i < argc; i++) {
		if(i > 2) {
			strncat(data, " ", 0x100);
		}
		strncat(data, argv[i].string, 0x100);
	}
	ret = radio_write(data);

	free(data);
	return ret;
}

int radio_write(char* command) {
	int size = 0;
	char data[0x100];
	memset(data, '\0', 0x100);
	strncpy(data, command, 0x100);
	strncat(data, "\r", 0x100);
	size = strlen(data);
	uart_write(1, data, size);
	return size;
}

int radio_read(char* buffer, unsigned int size) {
	return size;
}

void radio_set_debug() {
	radio_write("at+cmee=1");
	radio_write("at+creg=1");
}

int radio_find_commands() {
	srand(1);
	int i = 0;
	char string[8];
	char command[32];
	memset(string, '\0', 8);
	while(1) {
		memset(command, '\0', 32);
		strcpy(command, "at+");
		for(i = 0; i < 4; i++) {
			string[0] = (char) (rand() %  26) + 0x61;
			strncat(command, string, 32);
		}
		strncat(command, "=?", 32);
		radio_write(command);
		//radio_read(response);
	}
	return 0;
}

int radio_send_random() {
	int i = 0;
	char string[8];
	char command[32];
	memset(string, '\0', 8);
	memset(command, '\0', 32);
	strcpy(command, "at+");
	for(i = 0; i < 4; i++) {
		string[0] = (char) (rand() %  26) + 0x61;
		strncat(command, string, 32);
	}
	strncat(command, "=?", 32);
	printf("Sending \"%s\"\n", command);
	radio_write(command);
	return 0;
}

void radio_reader(void* arg) {
	char byte;
	while(1) {
		uart_read(1, &byte, 1, 1);
		printf("%c", byte);
	}
}
