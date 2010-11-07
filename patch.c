/**
  * GreenPois0n Cynanide - patch.c
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
#include <string.h>

#include "task.h"
#include "lock.h"
#include "patch.h"
#include "device.h"
#include "common.h"
#include "commands.h"

const unsigned char* patch_cert_seq = "\x4F\xF0\xFF\x30\xDD\xF8\x40\x24";
const unsigned char* patch_cert_seq2 = "\x01\x20\x40\x42\x88\x23\xDB\x00";
const unsigned char* patch_cert = "\x00\x20\x00\x20";

const unsigned char patch_perm_seq[] = "\x00\x38\x18\xBF\x01\x20\x80\xBD";
const unsigned char patch_perm[] = "\x01\x20\x01\x20";

const unsigned char patch_ecid_seq[] = "\x02\x94\x03\x94\x01\x90\x28\x46";
const unsigned char patch_ecid[] = "\x00\x20\x00\x20";

const unsigned char patch_command_seq1[] = "\x80\xb5\x00\xaf\x82\xb0\x4f\xf0";
const unsigned char patch_command_seq2[] = "\x90\xB5\x01\xAF\x84\xB0";

const unsigned char patch_command[] = "\x00\x4b\x18\x47\x00\x00\x00\x41";

int patch_init() {
	//printf("Initializing patches\n");
	cmd_add("patch", &patch_cmd, "patch firmware in memory");
	return 0;
}

int patch_cmd(int argc, CmdArg* argv) {
	unsigned int size = 0;
	unsigned char* address = NULL;
	if(argc != 3) {
		puts("usage: patch <address> <size>\n");
		puts("  address           \t\taddress to the image to patch\n");
		puts("  size              \t\tsize of image to search\n");
		return 0;
	}

	size = argv[2].uinteger;
	address = (unsigned char*) argv[1].uinteger;
	return patch_firmware(address, size);
}


int patch_kernel(unsigned char* address, unsigned int size) {
	unsigned int target = 0;
	/*
	CSED: 00 00 00 00 01 00 00 00 80 00 00 00 00 00 00 00 => 01 00 00 00 01 00 00 00 80 00 00 00 00 00 00 00 ; armv6 & armv7

	AMFI: 00 B1 00 24 20 46 90 BD  +  0 => 00 B1 01 24 20 46 90 BD ; armv7
	      0E 00 A0 E1 01 10 84 E2  + 20 => 00 00 00 00 ; armv6

	PROD: 00 23 00 94 01 95 02 95  + 10 => 00 20 00 20 ; armv7 & armv6

	ECID: 02 90 03 90 1D 49 50 46  + 12 => 00 20 00 20 ; armv7
	      02 90 03 90 06 9A 07 9B  + 12 => 00 20 00 20 ; armv6

	SHSH: D3 80 04 98 02 21 7C 4B  +  8 => 00 20 ; 4.0 armv7
	      98 47 50 B9 00 98 02 21  +  8 => 00 20 ; 3.0 armv7
	      0D D1 01 98 02 21 34 4B  +  8 => 00 20 ; 4.0 armv6


	????: 00 28 40 F0 CC 80 04 98  +  8 => 00 20 00 20 ; 4.0 armv7
	      28 B9 00 98 FF F7 03 FF  +  8 => 00 20 00 20 ; 3.0 armv7
	      07 D1 01 98 FF F7 FC FE  +  8 => 00 20 00 20 ; 4.0 armv6


	????: 1F 4C 1E E0 28 46 51 46  +  8 => 01 20 01 20

	SHA1: A0 47 08 B1 28 46 30 E0  +  8 => 00 20 00 20
          85 68 00 23 .. 93 .. 93 -        .. .. .. .. 29 46 04 22
	TFP0: 85 68 00 23 02 93 01 93  +  8 => 0B E0 C0 46 ; armv7
	      85 68 .. 93 .. 93 00 2c          0B D1
	      85 68 02 93 01 93 00 2C  +  8 => 0E 93 BD 93 ; armv6
	*/
	unsigned int i = 0;
	//enter_critical_section();
	for(i = 0; i < size; i++) {
#ifdef S5L8720X
		if(!memcmp(&address[i], "\x00\x00\x00\x00\x01\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00", 16)) {
			target = i;
			printf("Found armv6 kernel patch 1 at %p\n", &address[target]);
			memcpy(&address[target], "\x01\x00\x00\x00\x01\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x2E\xD1\x35\x98\x80\x07\x33\xD4\x6B\x08\x1E\x1C\xEB\x0A\x01\x22", 16)) {
			target = i;
			printf("Found armv6 kernel patch 1 at %p\n", &address[target]);
			memcpy(&address[target], "\x2E\xD1\x35\x98\x80\x07\x00\x28\x6B\x08\x1E\x1C\xEB\x0A\x01\x22", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x00\x40\xA0\xE3\x04\x00\xA0\xE1\x90\x80\xBD\xE8\x90\x5D\x3B\x80", 16)) {
			target = i;
			printf("Found armv6 kernel patch 2 at %p\n", &address[target]);
			memcpy(&address[target], "\x01\x40\xA0\xE3\x04\x00\xA0\xE1\x90\x80\xBD\xE8\x90\x5D\x3B\x80", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x00\x00\xE0\xE3\x1A\x00\x00\xEA\xC8\x30\x17\xE5\xC4\x40\x17\xE5", 16)) {
			target = i;
			printf("Found armv6 kernel patch 3 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x00\xA0\xE3\x1A\x00\x00\xEA\xC8\x30\x17\xE5\xC4\x40\x17\xE5", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x02\x95\x03\x94\xFF\xF7\x16\xFF\x00\x28\x1F\xD0\x1C\xE0\x00\x21", 16)) {
			target = i;
			printf("Found armv6 kernel patch 4 at %p\n", &address[target]);
			memcpy(&address[target], "\x02\x95\x03\x94\x00\x20\x00\x20\x00\x28\x1F\xD0\x1C\xE0\x00\x21", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x06\x9A\x07\x9B\x58\x46\x1C\x49\xFF\xF7\xFC\xFE\x43\x42\x18\x43", 16)) {
			target = i;
			printf("Found armv6 kernel patch 5 at %p\n", &address[target]);
			memcpy(&address[target], "\x06\x9A\x07\x9B\x58\x46\x1C\x49\x00\x20\x00\x20\x43\x42\x18\x43", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x7A\x4B\x98\x47\x00\x28\x00\xD0\xC5\xE0\x06\x98\xFF\xF7\x90\xFD", 16)) {
			target = i;
			printf("Found armv6 kernel patch 6 at %p\n", &address[target]);
			memcpy(&address[target], "\x7A\x4B\x98\x47\x00\x20\x00\xD0\xC5\xE0\x06\x98\xFF\xF7\x90\xFD", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x05\x1E\x00\xD0\xBF\xE0\x41\x46\x4B\x7C\x0A\x7C\x1B\x02\x1A\x43", 16)) {
			target = i;
			printf("Found armv6 kernel patch 7 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x25\x00\xD0\xBF\xE0\x41\x46\x4B\x7C\x0A\x7C\x1B\x02\x1A\x43", 16);
			continue;
		}
		if(!memcmp(&address[i], "\x53\x40\x1C\x43\xA8\x42\xF7\xD9\x00\x2C\x00\xD0\xFF\x24\x30\x1C", 16)) {
			target = i;
			printf("Found armv6 kernel patch 8 at %p\n", &address[target]);
			memcpy(&address[target], "\x53\x40\x1C\x43\xA8\x42\xF7\xD9\x00\x2C\x00\xD0\x00\x24\x30\x1C", 16);
			continue;
		}
		/*
		 * Patch 9
		 */
		if(!memcmp(&address[i], "\x02\x68\x85\x68\x02\x93\x01\x93", 8)) {
			target = i + 8;
			printf("Found kernel patch 9 at %p\n", &address[target]);
			memcpy(&address[target], "\xC0\x46\x0B\xE0", 4);
			continue;
		}
#else
		/*
		 * Patch 1
		 */
		if(!memcmp(&address[i], "\x00\x00\x00\x00\x01\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00", 16)) {
			target = i + 0;
			printf("Found kernel patch 1 at %p\n", &address[target]);
			memcpy(&address[target], "\x01\x00\x00\x00\x01\x00\x00\x00\x80\x00\x00\x00\x00\x00\x00\x00", 16);
			continue;
		}

		/*
		 * Patch 2
		 */
		if(!memcmp(&address[i], "\x00\xB1\x00\x24\x20\x46\x90\xBD", 8)) {
			target = i + 0;
			printf("Found armv7 kernel patch 2 at %p\n", &address[target]);
			memcpy((char*) &address[target], "\x00\xB1\x01\x24\x20\x46\x90\xBD", 8);
			continue;
		}
		if(!memcmp(&address[i], "\x0E\x00\xA0\xE1\x01\x10\x84\xE2", 8)) {
			target = i + 20;
			printf("Found armv6 kernel patch 2 at %p\n", &address[target]);
			memcpy((char*) &address[target], "\x00\x00\x00\x00", 4);
			continue;
		}

		/*
		 * Patch 3
		 */
		if(!memcmp(&address[i], "\x00\x23\x00\x94\x01\x95\x02\x95", 8)) {
			target = i + 10;
			printf("Found kernel patch 3 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20\x00\xD3\x80\x04\x98\x02\x21\x7C\x4B\x20", 4);
			continue;
		}

		/*
		 * Patch 4
		 */
		if(!memcmp(&address[i], "\x02\x90\x03\x90\x1D\x49\x50\x46", 8)) {
			target = i + 12;
			printf("Found armv7 kernel patch 4 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20\x00\x20", 4);
			continue;
		}
		if(!memcmp(&address[i], "\x02\x90\x03\x90\x06\x9A\x07\x9B", 8)) {
			target = i + 12;
			printf("Found armv6 kernel patch 4 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20\x00\x20", 4);
			continue;
		}

		/*
		 * Patch 5
		 */
		if(!memcmp(&address[i], "\xD3\x80\x04\x98\x02\x21\x7C\x4B", 8)
				|| !memcmp(&address[i], "\x98\x47\x50\xB9\x00\x98\x02\x21", 8)) {
			target = i + 8;
			printf("Found armv7 kernel patch 5 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20", 2);
			continue;
		}
		if(!memcmp(&address[i], "\x0D\xD1\x01\x98\x02\x21\x34\x4B", 8)) {
			target = i + 8;
			printf("Found armv6 kernel patch 5 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20", 2);
			continue;
		}

		/*
		 * Patch 6
		 */
		if(!memcmp(&address[i], "\x00\x28\x40\xF0\xCC\x80\x04\x98", 8)
				|| !memcmp(&address[i], "\x28\xB9\x00\x98\xFF\xF7\x03\xFF", 8)) {
			target = i + 8;
			printf("Found kernel patch 6 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20\x00\x20", 4);
			continue;
		}

		/*
		 * Patch 7
		 */
		if(!memcmp(&address[i], "\x1F\x4C\x1E\xE0\x28\x46\x51\x46", 8)) {
			target = i + 8;
			printf("Found kernel patch 7 at %p\n", &address[target]);
			memcpy(&address[target], "\x01\x20\x01\x20", 4);
			continue;
		}

		/*
		 * Patch 8
		 */
		if(!memcmp(&address[i], "\xA0\x47\x08\xB1\x28\x46\x30\xE0", 8)) {
			target = i + 8;
			printf("Found kernel patch 8 at %p\n", &address[target]);
			memcpy(&address[target], "\x00\x20\x00\x20", 4);
			continue;
		}

		/*
		 * Patch 9
		 */
		if(!memcmp(&address[i], "\x85\x68\x00\x23\x02\x93\x01\x93", 8) ||
				!memcmp(&address[i], "\x85\x68\x00\x23\x04\x93\x03\x93", 8)) {
			target = i + 8;
			printf("Found kernel patch 9 at %p\n", &address[target]);
			memcpy(&address[target], "\x0B\xE0\xC0\x46", 4);
			continue;
		}

#endif
	}
	//exit_critical_section();
	return 0;
}

int patch_firmware(unsigned char* address, int size) {
	unsigned int i = 0;
	/*
	CERT: "\x4F\xF0\xFF\x30\xDD\xF8\x40\x24" => "\x00\x20\x00\x20"; armv6
	      "\x01\x20\x40\x42\x88\x23\xDB\x00" => "\x00\x20\x00\x20"; armv7
	PERM: "\xf3\xdf\x90\xb5\x07\x4b\x1b\x68" => "\x4f\xf0\xff\x33"; armv7
	      "\x83\x43\xD8\x0F\x01\x23\x58\x40" => "\x01\x20\x01\x20"; armv6
	ECID: "\x02\x94\x03\x94\x01\x90\x28\x46" => "\x00\x20\x00\x20";
	CMD:  "\x80\xb5\x00\xaf\x82\xb0\x4f\xf0" => "\x00\x4b\x18\x47\x00\x00\x00\x41";
	      "\x90\xB5\x01\xAF\x84\xB0"
	*/

	printf("Finding RSA patch\n");
	unsigned char* cert_offset = patch_find(address, size, "\x4F\xF0\xFF\x30\xDD\xF8\x40\x24", 8);
	if(cert_offset == NULL) {
		cert_offset = patch_find(address, size, "\x01\x20\x40\x42\x88\x23\xDB\x00", 8);
		if(cert_offset == NULL) {
			printf("Unable to find RSA patch offset\n");
		} else {
			printf("Found RSA patch 2 offset at %p\n", cert_offset);
			memcpy(cert_offset, patch_cert, 4);
		}
	} else {
		printf("Found RSA patch 1 offset at %p\n", cert_offset);
		memcpy(cert_offset, patch_cert, 4);
	}

	unsigned char* image_load = find_function("image_load", LOADADDR, IBOOT_BASEADDR);
	printf("Found image_load offset at %p\n", image_load);
	if(image_load == NULL) {
		printf("Unable to find image_load function\n");
	} else {
		unsigned char* permission_offset = patch_find(image_load, size, "\x00\x38\x18\xBF\x01\x20\x80\xBD", 8);
		if(permission_offset == NULL) {
			permission_offset = patch_find(image_load, size, "\x83\x43\xD8\x0F\x01\x23\x58\x40", 8);
			if(permission_offset == NULL) {
				printf("Unable to find permission patch offset\n");
			} else {
				permission_offset += 2;
				printf("Found PERM patch offset at %p\n", permission_offset);
				memcpy(permission_offset, "\x01\x20\x01\x20", 4);
			}
		} else {
			permission_offset += 2;
			printf("Found PERM patch offset at %p\n", permission_offset);
			memcpy(permission_offset, patch_perm, 4);
		}
	}

	unsigned char* command = find_function("cmd_go", LOADADDR, IBOOT_BASEADDR);
	if(command == NULL) {
		printf("Unable to find command patch offset\n");
	} else {
		command--;
		printf("Found command patch offset at %p\n", command);
#ifdef S5L8720X
		memcpy(command, "\x00\x4b\x18\x47\x00\x00\x00\x09", 8);
#else
		memcpy(command, "\x00\x4b\x18\x47\x00\x00\x00\x41", 8);
#endif
	}

	return 0;
}

unsigned char* patch_find(unsigned char* start, int length, unsigned char* find, int size) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!memcmp(&start[i], find, size)) {
			return &start[i];
		}
	}
	return NULL;
}

unsigned char* patch_rfind(unsigned char* start, int length, unsigned char* find, int size) {
	int i = 0;
	for(i = length; i < length; i--) {
		if(!memcmp(&start[i], find, size)) {
			return &start[i];
		}
	}
	return NULL;
}
