/**
  * GreenPois0n Cynanide - iPad1,1/7B500/iBoot/offsets.h
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
#define TARGET_FREE                       (0xCA94+1)
#define TARGET_MALLOC                     (0xD2C8+1)
#define TARGET_JUMP_TO                    (0x1147C+1)
#define TARGET_PRINTF                     (0x1F1EC+1)
#define TARGET_VPRINTF                    (0x1EB38+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN             (0x29000)
#define TARGET_CMD_LIST_END               (0x2902C)

// Task functions
#define TARGET_TASK_YIELD                 (0x11D94+1)
#define TARGET_TASK_RUNNING               (0x2976C)
#define TARGET_TASK_LIST                  (0x29804)

// AES offsets
#define TARGET_AES_CRYPTO_CMD             (0x1300C+1)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x2D140)

// Image offsets
#define TARGET_IMAGE_LIST                 (0x2974C)

// Filesystem offsets
//#define TARGET_FS_MOUNT                   (0x0)
//#define TARGET_FS_UNMOUNT                 (0x0)
//#define TARGET_FS_LOAD_FILE               (0x0)

// NVRAM offsets
#define TARGET_NVRAM_LIST                 (0x29844)

#endif // OFFSETS_H
