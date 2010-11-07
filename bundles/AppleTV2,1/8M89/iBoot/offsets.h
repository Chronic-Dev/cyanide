/**
  * GreenPois0n Cynanide - AppleTV2,1/8M86/iBoot/offsets.h
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
#define TARGET_FREE                       (0x11F60+1)
#define TARGET_MALLOC                     (0x11F6C+1)
#define TARGET_JUMP_TO                    (0x15B14+1)
#define TARGET_PRINTF                     (0x24AE0+1)
#define TARGET_VPRINTF                    (0x0+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN             (0x31568)
#define TARGET_CMD_LIST_END               (0x31580)
#define TARGET_CMD_RAMDISK                (0xF84+1)

// Task functions
#define TARGET_TASK_YIELD                 (0x16438+1)
#define TARGET_TASK_RUNNING               (0x31428)
#define TARGET_TASK_LIST                  (0x314C0)

// AES offsets
#define TARGET_AES_CRYPTO_CMD             (0x1770C+1)

// BDev offsets
#define TARGET_BDEV_LIST                  (0xFFFFFFFF)

// Image offsets
#define TARGET_IMAGE_LIST                 (0x313F8)

// Filesystem offsets
#define TARGET_FS_MOUNT                   (0x19F40+1)
#define TARGET_FS_UNMOUNT                 (0x0+1)
#define TARGET_FS_LOAD_FILE               (0x1A0F0+1)

// Kernel offsets
#define TARGET_KERNEL_LOAD                (0x13924+1)
#define TARGET_KERNEL_PHYMEM              (0x362C0)
#define TARGET_KERNEL_BOOTARGS            (0x28C5C)

// NVRAM offset
#define TARGET_NVRAM_LIST                 (0x31504)

#endif // OFFSETS_H
