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

#include "common.h"
#include "commands.h"

Bool gGpHasInit = FALSE;

int gp_init() {
	if(cmd_init()) return -1;
	return 0;
}

int main(int argc, CmdArg* argv) {
	if(!gGpHasInit) {
		if(gp_init()) {
			puts("Unable to initialize greenpois0n!!\n");
			return -1;
		}
	}

	if(argc > 1) {
		int i = 0;
		char* command = argv[1].string;
		for(i = 0; i < gCmdCount; i++) {
			if(!strcmp(gCmdCommands[i]->name, command)) {
				return gCmdCommands[i]->handler(argc-1, &argv[1]);
			}
		}

		printf("Command Not Found\n\n");
		return -1;
	}

	return 0;
}

