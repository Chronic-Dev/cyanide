/**
  * GreenPois0n Cynanide - bdev.c
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

#include "bdev.h"
#include "lock.h"
#include "common.h"
#include "commands.h"

BdevDescriptor** gBdevList = (void*) SELF_BDEV_LIST;

void* find_bdev_list() {
	return 0;
}

int bdev_init() {
	//gBdevList = find_bdev_list();
	if(gBdevList == NULL) {
		puts("Unable to find gBdevList\n");
	} else {
		printf("Found gBdevList at 0x%x\n", gBdevList);
		cmd_add("bdev", &bdev_cmd, "read or write data to block devices");
	}
	return 0;
}

int bdev_cmd(int argc, CmdArg* argv) {
	char* action = NULL;
	char* device = NULL;
	void* source = NULL;
	unsigned int size = 0;
	void* destination = NULL;
	BdevDescriptor* bdev = NULL;

	if(argc < 2) {
		puts("usage: bdev <list/read/write> <bdev> [source] [size] [destination]\n");
		puts("  bdev         \t\tname of blockdevice\n");
		puts("  source       \t\tsource address of transaction");
		puts("  size         \t\tsize of transaction in bytes\n");
		puts("  destination  \t\tdestination address of transation\n\n");
		return 0;
	}

	action = argv[1].string;
	if(argc == 2) {
		if(!strcmp(action, "list")) {
			bdev_display_list();
			return 0;
		}
	}

	if(argc == 6) {
		device = argv[2].string;
		source = (void*) argv[3].uinteger;
		size = argv[4].uinteger;
		destination = (void*) argv[5].uinteger;
		BdevDescriptor* bdev = (BdevDescriptor*) bdev_find_device(device);
		if(!bdev) {
			puts("unknown block device\n\n");
			return -1;
		}

		if(!strcmp(action, "read")) {
			puts("reading... ");
			bdev_read(bdev, destination, source, size);
			puts("done\n\n");

		} else if(!strcmp(action, "write")) {
			puts("writing... ");
			bdev_write(bdev, source, destination, size);
			puts("done\n\n");
		}
	}

	return 0;
}

BdevDescriptor* bdev_find_device(const char* name) {
	BdevDescriptor* bdev = *gBdevList;
	while(bdev != NULL) {
		if(!strcmp(name, bdev->name)) {
			return bdev;
		}
		bdev = bdev->next;
	}
	return NULL;
}

void bdev_display_list() {
	BdevDescriptor* bdev = *gBdevList;
	enter_critical_section();
	printf("Block Devices:\n");
	while(bdev != NULL) {
		printf("  (0x%08x) name: %s size: %p\n", bdev, bdev->name, bdev->logicalSize);
		bdev = bdev->next;
	}
	printf("\n");
	exit_critical_section();
}

int bdev_read(BdevDescriptor* bdev, void* destination, void* source, unsigned int size) {
	enter_critical_section();
	printf("read: %p  write: %p\n", bdev->read, bdev->write);
	exit_critical_section();
	bdev->read(bdev, destination, source, 0, size);
	return size;
}

int bdev_write(BdevDescriptor* bdev, void* source, void* destination, unsigned int size) {
	bdev->write(bdev, destination, source, 0, size);
	return size;
}
