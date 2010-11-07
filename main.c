/**
  * GreenPois0n Cynanide - main.c
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

#include "aes.h"
#include "bdev.h"
#include "radio.h"
#include "nvram.h"
#include "image.h"
#include "patch.h"
#include "memory.h"
#include "kernel.h"
#include "common.h"
#include "commands.h"
#include "filesystem.h"
#include "framebuffer.h"

Bool gGpHasInit = FALSE;

int gp_init() {
	if(common_init()) return -1;
	if(cmd_init()) return -1;
	if(fb_init()) return -1;
	if(uart_init()) return -1;
	if(radio_init()) return -1;
	if(patch_init()) return -1;
	if(memory_init()) return -1;
	if(task_init()) return -1;
	if(aes_init()) return -1;
	if(bdev_init()) return -1;
	if(image_init()) return -1;
	if(nvram_init()) return -1;
	if(fs_init()) return -1;
	if(kernel_init()) return -1;

	gGpHasInit = TRUE;
	return 0;
}

int main(int argc, CmdArg* argv) {
	int i = 0;
	char result[0x10];
	if(!gGpHasInit || gCmdCount == 0) {
		if(gp_init()) {
			puts("Unable to initialize greenpois0n!!\n");
			return -1;
		}
		puts("Greenpois0n initialized\n");
		return 0;
	}

	for(i = 1; i < argc; i++) {
		if(!strcmp(argv[i].string, "$_")) {
			NvramVar* retval = nvram_find_var("?");
			argv[i].string = retval->string;
			continue;
		}
		if(argv[i].string[0] == '$') {
			NvramVar* var = nvram_find_var(&(argv[i].string[1]));
			if(var == NULL) {
				printf("Unable to find nvram var for %s\n", &(argv[i].string[1]));
			} else {
				argv[i].string = var->string;
			}
		}
	}

	if(argc > 1) {
		int i = 0;
		char* command = argv[1].string;
		for(i = 0; i < gCmdCount; i++) {
			if(!strcmp(gCmdCommands[i]->name, command)) {
				int ret = gCmdCommands[i]->handler(argc-1, &argv[1]);
				snprintf(result, 0xF, "0x%x", ret);
				nvram_set_var("cmd-results", result);
				return ret;
			}
		}

		printf("Command %s not found.\n\n", command);
		return -1;
	}

	return 0;
}

