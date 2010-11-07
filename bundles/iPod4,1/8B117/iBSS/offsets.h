/**
  * GreenPois0n Cynanide - iPod4,1/8B117/iBSS/offsets.h
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Joshua Hill
  * Copyright (C) 2010 Dustin Howett
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

// Task functions
#define TARGET_TASK_RUNNING               (0x22738)
#define TARGET_TASK_LIST                  (0x227D0)

// BDev offsets
#define TARGET_BDEV_LIST                  (0x26280)

// Kernel offsets
#define TARGET_KERNEL_PHYMEM              (0x267C0)

#endif // OFFSETS_H
