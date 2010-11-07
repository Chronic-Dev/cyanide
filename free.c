/**
  * GreenPois0n Cynanide - free.c
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


#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

void free(void* ptr) {
	chunk_header_t* chunk;
	chunk_header_t* next_chunk;
	chunk_header_t* prev_chunk;
	chunk_header_t* current_chunk;
	chunk_header_t** chunk_header;

	if (ptr) {
		chunk = (void*) ptr - 8;
		next_chunk = get_next_chunk(chunk);
		prev_chunk = get_prev_chunk(chunk);
		gHeapRemaining += chunk->size * 8;
		if (chunk == next_chunk || chunk == prev_chunk
				|| get_prev_chunk(next_chunk) != chunk
				|| get_next_chunk(prev_chunk) != chunk
				|| chunk->prev_size & 1) {
			puts("Heap Error\n");
		}

		chunk->prev_size |= 1;

		if ((chunk->prev_size << 30) < 0) {
			*prev_chunk->head = prev_chunk->next;
			if(prev_chunk->next) {
				prev_chunk->next->head = prev_chunk->head;
			}

			prev_chunk->size += chunk->size;
			chunk->size = 0;
			chunk->prev_size &= 3u;
			chunk = prev_chunk;
		}

		if ((next_chunk->prev_size << 31) < 0) {
			*next_chunk->head = next_chunk->next;
			if(next_chunk->next) {
				next_chunk->next->head = next_chunk->head;
			}

			chunk->size += next_chunk->size;
			next_chunk->size = 0;
			next_chunk->prev_size &= 3u;
		}

		next_chunk->prev_size |= 2;
		next_chunk->prev_size = (next_chunk->prev_size & 3) | (4 * chunk->size);

		chunk_header = &gHeapHeader[get_zone(chunk->size * 8)];
		current_chunk = *chunk_header;
		chunk->head = chunk_header;
		chunk->next = current_chunk;

		if(current_chunk) {
			current_chunk->head = &chunk;
		}

		*chunk_header = chunk;
	}
}
