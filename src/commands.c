/*
 *
 *  greenpois0n - payload/src/commands.c
 *  (c) 2010 Chronic-Dev Team
 *
 */

#include <stdio.h>
#include <string.h>

#include "lock.h"
#include "common.h"

int gCmdCount = 0;
Bool gCmdHasInit = FALSE;

CmdInfo** gCmdCommands = NULL;

void* gCmdListEnd = SELF_CMD_LIST_END;
void* gCmdListBegin = SELF_CMD_LIST_BEGIN;

/*
 * Private Functions
 */
int cmd_init() {
	if(gCmdHasInit) return 0;

	int i = 0;
	gCmdCount = 0;
	gCmdHasInit = TRUE;;
	gCmdCommands = (CmdInfo**) malloc(sizeof(CmdInfo*) * MAX_COMMANDS);

	// add all built in commands to our private commands
	CmdInfo** current = (CmdInfo**) gCmdListBegin;
	for (i = 0; &current[i] < (CmdInfo**) gCmdListEnd; i++) {
		cmd_add(current[i]->name, current[i]->handler, current[i]->description);
	}

	// add our essential commands
	cmd_add("help", &cmd_help, "display all available commands");
	cmd_add("echo", &cmd_echo, "write characters back to screen");

	return 0;
}

void cmd_add(char* name, CmdFunction handler, char* description) {
	CmdInfo* command = NULL;
	if(gCmdCount >= MAX_COMMANDS) {
		puts("Maximum Commands Reached\n");
		return;
	}

	command = (CmdInfo*) malloc(sizeof(CmdInfo));
	command->name = name;
	command->handler = handler;
	command->description = description;
	gCmdCommands[gCmdCount] = command;
	gCmdCount++;
}

int cmd_get_arg(CmdArg arg) {
	if (arg.type==CMDARG_TYPE_INTEGER) {
		return arg.uinteger;
	} else {
		char* ret = arg.string;
		int len = strlen(ret);
		// strip leading and trailing quotes if any
		if (len > 0 && (ret[len-1]=='"' || ret[len-1]=='\'')) ret[len-1]=0;
		if (ret[0]=='"' || ret[0]=='\'') ret = &ret[1];
		return (int) ret;
	}
}

void cmd_start() {
	printf_begin();
}

/*
 * Public Functions
 */
int cmd_help(int argc, CmdArg* argv) {
	cmd_start();

	int i = 0;
	enter_critical_section();
	printf("Commands:\n");
	for(i = 0; i < gCmdCount; i++) {
		printf("  %s \t", gCmdCommands[i]->name);
		if(strlen(gCmdCommands[i]->name) < 5) printf(" \t");
		printf("%s\n", gCmdCommands[i]->description);
	}
	printf("\n");
	exit_critical_section();

	return 0;
}

int cmd_echo(int argc, CmdArg* argv) {
	cmd_start();

	int i = 0;
	if(argc >= 2) {
		enter_critical_section();
		for(i = 1; i < argc; i++) {
			printf("%s ", argv[i].string);
		}
		printf("\n");
		exit_critical_section();
		return 0;
	}
	
	puts("usage: echo <message>\n");
	return 0;
}

