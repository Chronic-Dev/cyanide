/**
  * GreenPois0n Cynanide - filesystem.h
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

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "common.h"
#include "device.h"
#include "offsets.h"
#include "commands.h"

#ifdef TARGET_FS_UNMOUNT
#	define SELF_FS_UNMOUNT ((void*)(TARGET_BASEADDR + TARGET_FS_UNMOUNT))
#endif
#ifdef TARGET_FS_LOAD_FILE
#	define SELF_FS_LOAD_FILE ((void*)(TARGET_BASEADDR + TARGET_FS_LOAD_FILE))
#endif

#ifndef SELF_FS_UNMOUNT
#	define SELF_FS_UNMOUNT 0
#	warning "SELF_FS_UNMOUNT not defined"
#endif
#ifndef SELF_FS_LOAD_FILE
#	define SELF_FS_LOAD_FILE 0
#	warning "SELF_FS_LOAD_FILE not defined"
#endif

extern void(*fs_unmount)(const char *path);
extern int(*fs_load_file)(const char *path, void* address, unsigned int* size);
extern void(*fs_mount)(const char *partition, const char *type, const char *path);

int fs_init();
int fs_cmd(int argc, CmdArg* argv);

#endif /* FILESYSTEM_H */
