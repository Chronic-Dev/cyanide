/**
  * GreenPois0n Cynanide - filesystem.c
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

#include "filesystem.h"

int(*fs_load_file)(const char *path, void* address, unsigned int* size) = SELF_FS_LOAD_FILE;
void(*fs_mount)(const char *partition, const char *type, const char *path) = NULL;
void(*fs_unmount)(const char *path) = SELF_FS_UNMOUNT;

void* find_fs_mount() {
	return find_function("fs_mount", TARGET_BASEADDR, TARGET_BASEADDR);
}

void* find_fs_unmount() {
	return 0;
}

void* find_fs_load_file() {
	return 0;
}

int fs_init() {
	fs_mount = find_fs_mount();
	if(fs_mount == NULL) {
		puts("Unable to find fs_mount\n");
	} else {
		printf("Found fs_mount at 0x%x\n", fs_mount);
	}

	//fs_unmount = find_fs_unmount();
	if(fs_unmount == NULL) {
		puts("Unable to find fs_unmount\n");
	} else {
		printf("Found fs_unmount at 0x%x\n", fs_unmount);
	}

	//fs_load_file = find_fs_load_file();
	if(fs_load_file == NULL) {
		puts("Unable to find fs_load_file\n");
	} else {
		printf("Found fs_load_file at 0x%x\n", fs_load_file);
	}

	if(fs_mount && fs_unmount && fs_load_file) {
		cmd_add("fs", &fs_cmd, "perform operations on the filesystem");
	}

	return 0;
}

int fs_cmd(int argc, CmdArg* argv) {
	char* path = NULL;
	char* action = NULL;
	char* device = NULL;
	void* address = NULL;
	unsigned int* size = 0;

	if(argc < 3) {
		puts("usage: fs <mount/unmount/load> [options]\n");
		puts("  mount <device> <path> \tmount device to path\n");
		puts("  unmount <path>        \tunmount specified path\n");
		puts("  load <path> <address> \tload file from path to address\n\n");
		return 0;
	}

	action = argv[1].string;
	if(argc == 3) {
		if(strcmp(action, "umount")) {
				path = argv[2].string;
				fs_unmount(path);
		}

	} else if(argc == 4) {
		if(!strcmp(action, "mount")) {
			path = argv[3].string;
			device = argv[2].string;
			fs_mount(device, "hfs", path);

		} else if(!strcmp(action, "load")) {
			path = argv[2].string;
			address = (void*) argv[3].uinteger;
			fs_load_file(path, address, size);
		}
	}

	return 0;
}
