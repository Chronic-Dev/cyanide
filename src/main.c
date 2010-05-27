/*
 *
 *  greenpois0n - payload/src/main.c
 *  (c) 2010 Chronic-Dev Team
 *
 */

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

