/**
  * GreenPois0n Cynanide - iPod4,1/8B117/iBoot/offsets.h
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
#define TARGET_BASEADDR                   (0x5FF00000)

// Task functions
#define TARGET_TASK_RUNNING               (0x37734) 
#define TARGET_TASK_LIST                  (0x377CC)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x3B940)

// Filesystem offsets
#define TARGET_FS_UNMOUNT                 (0x19A50+1)
#define TARGET_FS_LOAD_FILE               (0x199E8+1)

// Kernel offsets
#define TARGET_KERNEL_PHYMEM              (0x3CA80)

#endif // OFFSETS_H
