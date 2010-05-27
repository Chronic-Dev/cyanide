/*
 *
 *	greenpois0n - payload/include/common.h
 *	(c) 2010 Chronic-Dev Team
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include "device.h"

#ifdef IBOOT
#	include "iboot.h"
#else
#	include "ibss.h"
#endif

#ifdef IBOOT /* IBOOT */
#	ifdef IBOOT_PRINTF
#		define SELF_PRINTF ((void*)(IBOOT_BASEADDR + IBOOT_PRINTF))
#	endif
#	ifdef IBOOT_VPRINTF
#		define SELF_VPRINTF ((void*)(IBOOT_BASEADDR + IBOOT_VPRINTF))
#	endif
#	ifdef IBOOT_MALLOC
#		define SELF_MALLOC ((void*)(IBOOT_BASEADDR + IBOOT_MALLOC))
#	endif
#	ifdef IBOOT_FREE
#		define SELF_FREE ((void*)(IBOOT_BASEADDR + IBOOT_FREE))
#	endif
#else
#	ifdef IBSS_PRINTF
#		define SELF_PRINTF ((void*)(IBSS_BASEADDR + IBSS_PRINTF))
#	endif
#	ifdef IBSS_MALLOC
#		define SELF_MALLOC ((void*)(IBSS_BASEADDR + IBSS_MALLOC))
#	endif
#	ifdef IBSS_FREE
#		define SELF_FREE ((void*)(IBSS_BASEADDR + IBSS_FREE))
#	endif
#endif

#ifndef SELF_PRINTF
#	define SELF_PRINTF 0
#	error "SELF_PRINTF not defined"
#endif

#ifndef SELF_VPRINTF
#	define SELF_VPRINTF 0
#	error "SELF_VPRINTF not defined"
#endif

#ifndef SELF_MALLOC
#	define SELF_MALLOC 0
#	error "SELF_MALLOC not defined"
#endif

#ifndef SELF_FREE
#	define SELF_FREE 0
#	error "SELF_FREE not defined"
#endif

#define FLIPENDIAN(x) flip_endian((unsigned char*)(&(x)), sizeof(x))

#define GETREG32(addr) (*((unsigned int*) addr))
#define SETREG32(addr, val) (*(volatile unsigned int*) addr = val)

#define GETREG16(addr) (*((unsigned short*) addr))
#define SETREG16(addr, val) (*(volatile unsigned short*) addr = val)

#ifdef NULL
#undef NULL
#define NULL 0
#endif

#define free _free
#define puts _puts
#define printf _printf
#define vprintf _vprintf
#define malloc _malloc

typedef enum {
	TRUE = 1,
	FALSE = 0
} Bool;

typedef struct LinkedList {
	void* prev;
	void* next;
} LinkedList;

extern void(*_free)(void* ptr);
extern void _puts(const char* message);
extern void*(*_malloc)(unsigned int size);
extern int(*_printf)(const char *format, ...);

static inline void flip_endian(unsigned char* x, int length) {
	unsigned int i = 0;
	unsigned char tmp = '\0';
	for(i = 0; i < (length / 2); i++) {
		tmp = x[i];
		x[i] = x[length - i - 1];
		x[length - i - 1] = tmp;
	}
}

int gpprintf(const char *format, ...);
void printf_begin();

#endif /* COMMON_H */
