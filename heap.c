/**
  * GreenPois0n Cynanide - heap.c
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


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

uint32_t gHeapRemaining;
uint32_t gHeapChunkCount;
heap_chunk_t gHeapChunkList[3];
chunk_header_t* gHeapHeader[32];

void heap_add_chunk(void* address, uint32_t size) {
	chunk_header_t* chunk;
	chunk_header_t* last_chunk;
	chunk_header_t* first_chunk;

	if(gHeapChunkCount > 3) {
		puts("Too many chunks\n");
		return;
	}
	memset(address, '\0', size);

	gHeapChunkList[gHeapChunkCount].address = address;
	gHeapChunkList[gHeapChunkCount].size = size;
	gHeapChunkCount++;

	chunk = address;
	chunk->prev_size &= 0xFCu;
	chunk->prev_size &= 3u;
	chunk->size = 1;

	first_chunk = get_next_chunk(chunk);
	first_chunk->prev_size &= 0xFCu;
	first_chunk->prev_size = (first_chunk->prev_size & 7) | 4;
	first_chunk->size = (size / 8) - 2;

	last_chunk = get_next_chunk(first_chunk);
	last_chunk->prev_size &= 0xFCu;
	last_chunk->prev_size = (last_chunk->prev_size & 3) | (4 * first_chunk->size);
	last_chunk->size = 1;

	free((void*) first_chunk + 8);
}

uint32_t get_zone(uint32_t size) {
	return (uint32_t) log(size/8);
}

uint32_t get_min_alloc(uint32_t size) {
	uint32_t result = (size + 15) & 0xFFFFFFF8;
	if(result <= 0xF) {
		result = 16;
	}
	return result;
}

chunk_header_t* get_next_chunk(chunk_header_t* chunk) {
	return (void*) chunk + (8 * chunk->size);
}

chunk_header_t*_get_prev_chunk(chunk_header_t* chunk) {
	return (void*) chunk - (8 * (chunk->prev_size >> 2));
}
