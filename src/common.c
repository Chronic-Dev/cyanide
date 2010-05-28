/**
  * GreenPois0n Cynanide - common.c
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

#include <stdarg.h>

//#include "task.h"
//#include "lock.h"
#include "common.h"

void(*_free)(void* ptr) = SELF_FREE;
void*(*_malloc)(unsigned int size) = SELF_MALLOC;
int(*_printf)(const char *fmt, ...) = SELF_PRINTF;
int(*_vprintf)(const char *fmt, ...) = SELF_VPRINTF;

int cout_count = 0;

void _puts(const char* message) {
	printf("%s", message);
}

void hexdump(unsigned char* buf, unsigned int len) {
	int i, j;
	enter_critical_section();
	printf("0x%08x: ", buf);
	for (i = 0; i < len; i++) {
		if (i % 16 == 0 && i != 0) {
			for (j=i-16; j < i; j++) {
				unsigned char car = buf[j];
				if (car < 0x20 || car > 0x7f) car = '.';
				printf("%c", car);
			}
			printf("\n0x%08x: ", buf+i);
		}
		printf("%02x ", buf[i]);
	}

	int done = (i % 16);
	int remains = 16 - done;
	if (done > 0) {
		for (j = 0; j < remains; j++) {
			printf("   ");
		}
	}

	if ((i - done) >= 0) {
		if (done == 0 && i > 0) done = 16;
		for (j = (i - done); j < i; j++) {
			unsigned char car = buf[j];
			if (car < 0x20 || car > 0x7f) car = '.';
			printf("%c", car);
		}
	}

	printf("\n\n");
	exit_critical_section();
}

void printf_begin() {
	cout_count = 0;
}

void printf_filler() {
	int blanks = (0x201 - (cout_count % 0x200));
	if (blanks > 100 || blanks == 0) return;
	int i;
	for (i = 0; i < blanks; i++) {
		_printf("");
	}
	printf_begin();
}

int gpprintf(const char* fmt, ...) {
	int ret;
	va_list args;
	enter_critical_section();
	
	va_start(args, fmt);
	ret = vprintf(fmt, args);
	va_end(args);
	
	cout_count += ret;
	printf_filler();
	exit_critical_section();

	return ret;
}
