/**
  * GreenPois0n Cynanide - iPod3,1/7D11/iBSS/offsets.h
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
#define TARGET_BASEADDR			(0x0)

// Standard offsets
#define TARGET_FREE                     (0x0+1)
#define TARGET_MALLOC                   (0x0+1)
#define TARGET_PRINTF                   (0x0+1)
#define TARGET_VPRINTF                  (0x0+1)

// Command offsets
#define TARGET_CMD_LIST_BEGIN           (0x0)
#define TARGET_CMD_LIST_END             (0x0)

// Task functions
#define TARGET_TASK_YIELD                (0x0+1)
#define TARGET_TASK_RUNNING              (0x0)
#define TARGET_TASK_LIST                 (0x0)

#endif // OFFSETS_H
