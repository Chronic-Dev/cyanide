/**
  * GreenPois0n Cynanide - aes.c
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
#include <string.h>

#include "aes.h"
#include "common.h"

int(*aes_crypto_cmd)(AesOption option, void* input, void* output,
		unsigned int size, AesMode mode, void* iv, void* key) = (void*) TARGET_AES_CRYPTO_CMD;


unsigned int aes_decrypt_key(unsigned char* in, unsigned char** out) {
	int i = 0;
	unsigned int size = 0;
	unsigned int byte = 0;
	unsigned char* data = *out;
	if(data == NULL) {
		return 0;
	}

	size = strlen(in) / 2;
	if(size > kAesSizeMax || size < kAesSizeMin) {
		return 0;
	}

	for(i = 0; i < size; i++) {
		sscanf(in, "%02x", &byte);
		data[i] = byte;
		in += 2;
	}

	aes_crypto_cmd(kAesDecrypt, data, data, size, kAesTypeGid, 0, 0);
	return size;
}

unsigned int aes_encrypt_key(unsigned char* in, unsigned char** out) {
	int i = 0;
	unsigned int size = 0;
	unsigned int byte = 0;
	unsigned char* data = *out;
	if(data == NULL) {
		return 0;
	}

	size = strlen(in) / 2;
	if(size > kAesSizeMax || size < kAesSizeMin) {
		return 0;
	}

	for(i = 0; i < size; i++) {
		sscanf(in, "%02x", &byte);
		data[i] = byte;
		in += 2;
	}

	aes_crypto_cmd(kAesEncrypt, data, data, size, kAesTypeGid, 0, 0);
	return size;
}
