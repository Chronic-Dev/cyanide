/*
 *
 *  greenpois0n - payload/include/commands.h
 *  (c) 2010 Chronic-Dev Team
 *
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "device.h"

#ifdef IBOOT
#	include "iboot.h"
#else
#	include "ibss.h"
#endif

#ifdef IBOOT /* IBOOT */
#	ifdef IBOOT_CMD_LIST_BEGIN
#		define SELF_CMD_LIST_BEGIN ((void*)(IBOOT_BASEADDR + IBOOT_CMD_LIST_BEGIN))
#	endif
#	ifdef IBOOT_CMD_LIST_END
#		define SELF_CMD_LIST_END ((void*)(IBOOT_BASEADDR + IBOOT_CMD_LIST_END))
#	endif
#else
#	ifdef IBSS_CMD_LIST_BEGIN
#		define SELF_CMD_LIST_BEGIN ((void*)(IBSS_BASEADDR + IBSS_CMD_LIST_BEGIN))
#	endif
#	ifdef IBSS_CMD_LIST_END
#		define SELF_CMD_LIST_END ((void*)(IBSS_BASEADDR + IBSS_CMD_LIST_END))
#	endif
#endif

#ifndef SELF_CMD_LIST_BEGIN
#	define SELF_CMD_LIST_BEGIN 0
#	error "SELF_CMD_LIST_BEGIN not defined"
#endif

#ifndef SELF_CMD_LIST_END
#	define SELF_CMD_LIST_END 0
#	error "SELF_CMD_LIST_END not defined"
#endif

#define MAX_COMMANDS 30

#define CMDARG_TYPE_STRING 0
#define CMDARG_TYPE_INTEGER 1

typedef struct CmdArg {
	signed int unk1;
	unsigned int uinteger;
	signed int integer;
	unsigned int type;
	unsigned char* string;
} CmdArg;

typedef int(*CmdFunction)(int argc, CmdArg* argv);

typedef struct CmdInfo {
	char* name;
	CmdFunction handler;
	char* description;
} CmdInfo;

extern void* gCmdListBegin;
extern void* gCmdListEnd;

extern int gCmdCount;
extern Bool gCmdHasInit;
extern CmdInfo** gCmdCommands;

int cmd_init();
void cmd_add(char* name, CmdFunction handler, char* description);

int cmd_help(int argc, CmdArg* argv);
int cmd_echo(int argc, CmdArg* argv);

#endif
