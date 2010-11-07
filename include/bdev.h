/*
 *
 *  greenpois0n - payload/include/bdev.h
 *  (c) 2010 Chronic-Dev Team
 *
 */

#ifndef BDEV_H
#define BDEV_H

#include "common.h"
#include "device.h"
#include "offsets.h"
#include "commands.h"

#ifdef TARGET_BDEV_LIST
#	define SELF_BDEV_LIST ((void*)(TARGET_BASEADDR + TARGET_BDEV_LIST))
#endif

#ifndef SELF_BDEV_LIST
#	define SELF_BDEV_LIST 0
#	error "SELF_BDEV_LIST not defined"
#endif

typedef struct BdevDescriptor {
    struct BdevDescriptor* next;
    void* unk1;
    unsigned int blockSize;
    unsigned int numOfBlocks;
    unsigned int unk2;
    unsigned long long logicalSize;
    void(*read)(struct BdevDescriptor* bdev, void* source, void* destination, unsigned int unk, unsigned int size);
    void(*default_block_read)();
    void(*write)(struct BdevDescriptor* bdev, void* source, void* destination, unsigned int unk, unsigned int size);
    void(*default_block_write)();
    void(*default_block_erase)();
    char name[0x10];
} BdevDescriptor;

extern BdevDescriptor** gBdevList;

int bdev_init();
int bdev_cmd(int argc, CmdArg* argv);
void bdev_display_list();
BdevDescriptor* bdev_find_device(const char* name);

int bdev_read(BdevDescriptor* bdev, void* destination, void* source, unsigned int size);
int bdev_write(BdevDescriptor* bdev, void* source, void* destination, unsigned int size);

#endif // BDEV_H
