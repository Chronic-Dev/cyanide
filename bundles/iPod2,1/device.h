/**
  * GreenPois0n Cynanide - iPhone3,1/device.h
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

#ifndef DEVICE_H
#define DEVICE_H

#define S5L8720X
#define LOADADDR           0x09000000
#define FRAMEBUFFER        0x0FC00000
#define FRAMEBUFFER_WIDTH  320
#define FRAMEBUFFER_HEIGHT 480
#define IBOOT_BASEADDR     0x0FF00000
#define IBEC_BASEADDR      0x0FF00000
#define IBSS_BASEADDR      0x22000000
#define LLB_BASEADDR       0x22000000
#define KERNEL_PATH        "/boot/System/Library/Caches/com.apple.kernelcaches/kernelcache"

#endif // DEVICE_H
