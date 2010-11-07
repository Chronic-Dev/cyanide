/**
  * GreenPois0n Cynanide - iPod3,1/8B117/iBSS/offsets.h
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
#define TARGET_BASEADDR                   (0x84000000)

// Standard offsets
#define TARGET_FREE                       (0xE048+1)
#define TARGET_MALLOC                     (0xE2CC+1)
#define TARGET_JUMP_TO                    (0x121AC+1)
#define TARGET_PRINTF                     (0x17664+1)
#define TARGET_VPRINTF                    (0x16F34+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN             (0x1E000)
#define TARGET_CMD_LIST_END               (0x1E02C)

// Task functions
#define TARGET_TASK_YIELD                 (0x12AA8+1)
#define TARGET_TASK_RUNNING               (0x1E984)
#define TARGET_TASK_LIST                  (0x1EA1C)

// AES offsets
#define TARGET_AES_CRYPTO_CMD             (0x13CE8+1)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x21680)

// Image offsets
#define TARGET_IMAGE_LIST                 (0x1E954)

// Filesystem offsets
//#define TARGET_FS_MOUNT                   (0x0)
//#define TARGET_FS_UNMOUNT                 (0x0)
//#define TARGET_FS_LOAD_FILE               (0x0)

// Kernel offsets
#define TARGET_KERNEL_LOAD                (0xF5E4+1)
#define TARGET_KERNEL_PHYMEM              (0x21BC0)
#define TARGET_KERNEL_BOOTARGS            (0x1BA04)

// NVRAM offsets
#define TARGET_NVRAM_LIST                 (0x1EA5C)

#endif // OFFSETS_H
