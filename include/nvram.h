/**
  * GreenPois0n Cynanide - nvram.h
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

#ifndef NVRAM_H
#define NVRAM_H

#include "common.h"
#include "device.h"
#include "offsets.h"
#include "commands.h"

typedef struct NvramVar {
	struct NvramVar* prev;
	struct NvramVar* next;
	unsigned char* string;
	unsigned int integer;
	unsigned int save;
	char name[0x40];
} NvramVar;

extern LinkedList* gNvramList;

int nvram_init();
int nvram_cmd(int argc, CmdArg* argv);
void nvram_display_list();
int nvram_get_var(const char* name);
int nvram_remove_var(const char* name);
NvramVar* nvram_find_var(const char* name);
int nvram_set_var(const char* name, const char* value);


#endif /* NVRAM_H */
