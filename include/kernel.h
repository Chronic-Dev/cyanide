/**
  * GreenPois0n Cynanide - kernel.h
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

#ifndef KERNEL_H
#define KERNEL_H

#include "common.h"
#include "device.h"
#include "offsets.h"
#include "commands.h"

#ifdef TARGET_KERNEL_PHYMEM
#	define SELF_KERNEL_PHYMEM ((void*)(TARGET_BASEADDR + TARGET_KERNEL_PHYMEM))
#endif

#ifndef SELF_KERNEL_PHYMEM
#	define SELF_KERNEL_PHYMEM 0
#	warning "SELF_KERNEL_PHYMEM not defined"
#endif

extern char* gBootArgs;
extern char** gKernelPhyMem;
extern int(*kernel_atv_load)(char* boot_path, char** output);
extern int(*kernel_load)(void* input, int max_size, char** output);

int kernel_init();
int kernel_cmd(int argc, CmdArg* argv);
int kernel_patch(void* address);

#endif /* KERNEL_H */
