/**
  * GreenPois0n Cynanide - commands.h
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

#ifndef COMMANDS_H
#define COMMANDS_H

#include "device.h"
#include "offsets.h"

#define MAX_COMMANDS 40

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

extern unsigned char* gCmdListBegin;
extern unsigned char* gCmdListEnd;

extern int gCmdCount;
extern Bool gCmdHasInit;
extern CmdInfo** gCmdCommands;

extern int(*jump_to)(int flags, void* addr, int phymem);
extern int(*load_ramdisk)(int argc);

int cmd_init();
void cmd_add(char* name, CmdFunction handler, char* description);

int cmd_help(int argc, CmdArg* argv);
int cmd_echo(int argc, CmdArg* argv);
int cmd_hexdump(int argc, CmdArg* argv);
int cmd_jump(int argc, CmdArg* argv);
int cmd_mw(int argc, CmdArg* argv);
int cmd_md(int argc, CmdArg* argv);
int cmd_call(int argc, CmdArg* argv);
int cmd_fsboot(int argc, CmdArg* argv);
int cmd_rdboot(int argc, CmdArg* argv);
int cmd_ramdisk(int argc, CmdArg* argv);
int cmd_test(int argc, CmdArg* argv);

#endif
