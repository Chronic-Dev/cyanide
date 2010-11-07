/**
  * GreenPois0n Cynanide - iPhone3,1/8B117/iBoot/offsets.h
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

#ifndef OFFSETS_H
#define OFFSETS_H

// Base address
#define TARGET_BASEADDR                   (0x5FF00000)

// Standard offsets
#define TARGET_FREE                       (0x12BB8+1)	// image3_free
#define TARGET_MALLOC                     (0x12BC4+1)	// image3_malloc
#define TARGET_JUMP_TO                    (0x1684C+1)
#define TARGET_PRINTF                     (0x2C3D4+1)
#define TARGET_VPRINTF                    (0x2BCA4+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN             (0x399D8)
#define TARGET_CMD_LIST_END               (0x399F0)
//#define TARGET_CMD_RAMDISK                (0x1058+1)

// Task functions
#define TARGET_TASK_YIELD                 (0x17170+1)
#define TARGET_TASK_RUNNING               (0x3987C)
#define TARGET_TASK_LIST                  (0x39914)

// AES offsets
#define TARGET_AES_CRYPTO_CMD             (0x185AC+1)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x3D800)

// Image offsets
#define TARGET_IMAGE_LIST                 (0x3984C) 

// Filesystem offsets
#define TARGET_FS_MOUNT                   (0x1ADC0+1)
#define TARGET_FS_UNMOUNT                 (0x1AFD8+1)
#define TARGET_FS_LOAD_FILE               (0x1AF70+1)

// Kernel offsets
#define TARGET_KERNEL_LOAD                (0x13708+1)
#define TARGET_KERNEL_PHYMEM              (0x3EC40)

// NVRAM offset
#define TARGET_NVRAM_LIST                 (0x39958)

#endif // OFFSETS_H
