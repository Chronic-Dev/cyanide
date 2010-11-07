/*
 *
 *  greenpois0n - payload/include/breakpoint.h
 *  (c) 2010 Chronic-Dev Team
 *
 */

#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include "common.h"
#include "commands.h"

#define BKPT_THUMB ((unsigned short) 0xbe00)
#define BKPT_ARM ((unsigned int) 0xe1200071)

typedef struct BreakpointEntry {
	unsigned int            id;
	Bool                    reset;
	unsigned int            value;
	void*                   address;
	void*			hexdump_address;
	unsigned int		hexdump_len;
	struct BreakpointEntry* next;
} BreakpointEntry;

typedef struct BreakpointLog {
	unsigned int	id;
	unsigned int	bp_id;
	unsigned int	pc;
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	unsigned int	r3;
	unsigned int	r4;
	unsigned int	r5;
	unsigned int	r6;
	unsigned int	r7;
	unsigned int	r8;
	unsigned int	r9;
	unsigned int	r10;
	unsigned int	r11;
	unsigned int	r12;
	unsigned int	sp;
	unsigned int	lr;
	unsigned int	spsr;
	unsigned int	stack[0x10];
	void*		hexdump_address;
	unsigned int	hexdump_len;
	unsigned int*	hexdump_result;
	struct BreakpointLog *next;
} BreakpointLog;

/*
 * Public Functions
 */

int break_init();
int break_cmd(int argc, CmdArg* argv);
void breakpoint_list();
BreakpointEntry* breakpoint_add(void* address, Bool reset);
Bool breakpoint_remove(unsigned int id);
void breakpoint_log_list();
void breakpoint_log_show(unsigned int id);
void breakpoint_log_clear();
BreakpointLog* breakpoint_log_find(unsigned int id);
void breakpoint_log_add(BreakpointLog *log);
BreakpointLog* breakpoint_log_remove(unsigned int id);

/*
 * Private Functions
 */
void breakpoint(unsigned int* stack);

#endif /* BREAKPOINT_H */
