/**
  * GreenPois0n Cynanide - functions.h
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

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

unsigned int find_reference(unsigned char* data, unsigned int base, unsigned int size, unsigned int address);
unsigned int find_top(unsigned char* data, unsigned int base, unsigned int size, unsigned int address);
unsigned int find_offset(unsigned char* data, unsigned int base, unsigned int size, unsigned char** what);
unsigned int find_string(unsigned char* data, unsigned int base, unsigned int size, const char* name);
void* find_function(const char* name, unsigned char* target, unsigned char* base);

#endif /* LOCK_H */

