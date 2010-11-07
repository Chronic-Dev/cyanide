/**
  * GreenPois0n Cynanide - iPod3,1/8B117/iBoot/offsets.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Nicolas Haunold
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

#ifndef OFFSETS_H
#define OFFSETS_H

// Base address
#define TARGET_BASEADDR                   (0x4FF00000)

// Standard offsets
#define TARGET_FREE                       (0xFD74+1)	// image3_free
#define TARGET_MALLOC                     (0xFD80+1)	// image3_malloc
#define TARGET_JUMP_TO                    (0x13728+1)
#define TARGET_PRINTF                     (0x22458+1)
#define TARGET_VPRINTF                    (0x21D28+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN             (0x2CAC0)
#define TARGET_CMD_LIST_END               (0x2CAD8)
//#define TARGET_CMD_RAMDISK                (0xDEAD+1)

// Task functions
#define TARGET_TASK_YIELD                 (0x1404C+1)
#define TARGET_TASK_RUNNING               (0x2C980)
#define TARGET_TASK_LIST                  (0x2CA18)

// AES offsets
#define TARGET_AES_CRYPTO_CMD             (0x152BC+1)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x30100)

// Image offsets
#define TARGET_IMAGE_LIST                 (0x2C950) 

// Filesystem offsets
#define TARGET_FS_MOUNT                   (0x17AB4+1)
#define TARGET_FS_UNMOUNT                 (0x17CCC+1)
#define TARGET_FS_LOAD_FILE               (0x17C64+1)

// Kernel offsets
#define TARGET_KERNEL_LOAD                (0x108C4+1)
#define TARGET_KERNEL_PHYMEM              (0x30E40)

// NVRAM offset
#define TARGET_NVRAM_LIST                 (0x2CA5C)

#endif // OFFSETS_H
