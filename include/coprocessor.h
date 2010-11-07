/**
  * GreenPois0n Cynanide - coprocessor.c
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

#ifndef COPROCESSOR_H
#define COPROCESSOR_H

// c0
int read_processor_id();
int read_processor_features();
int read_silicon_id();

// c1
int read_control_register();
void write_control_register(int value);
int read_auxcontrol_register();
void write_auxcontrol_register(int value);

// c2
int read_TBB0();
void write_TBB0(int value);

// c3
int read_DAC();
void write_DAC(int value);

// c7
void clear_icache();
//void clear_dcache(); //pod2g: removed, not armv6 compatible

// multiple
//void clear_cpu_caches(); //pod2g: removed, not armv6 compatible

#endif
