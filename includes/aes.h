/*
 *
 *  greenpois0n - payload/include/aes.h
 *  (c) 2010 Chronic-Dev Team
 *
 */

#ifndef AES_H
#define AES_H

#include "device.h"
#include "offsets.h"

#ifdef TARGET_AES_CRYPTO_CMD
#	define SELF_AES_CRYPTO_CMD ((void*)(TARGET_BASEADDR + TARGET_AES_CRYPTO_CMD))
#endif

#ifndef SELF_AES_CRYPTO_CMD
#	define SELF_AES_CRYPTO_CMD 0
#	error "SELF_AES_CRYPTO_CMD not defined"
#endif

#define kAesSizeMin 0x20
#define kAesSizeMax 0x30

typedef enum {
#ifdef S5L8900X
	kAesTypeGid = 0x200,
	kAesTypeUid = 0x201
#else
	kAesTypeGid = 0x20000200,
	kAesTypeUid = 0x20000201
#endif /* S5L8900X */
} AesMode;

typedef enum {
	kAesEncrypt = 0x10,
	kAesDecrypt = 0x11
} AesOption;

typedef enum {
	kAesType128 = 0x00000000,
	kAesType192 = 0x10000000,
	kAesType256 = 0x20000000
} AesType;

typedef enum {
	kAesSize128 = 0x20,
	kAesSize192 = 0x28,
	kAesSize256 = 0x30
} AesSize;

extern int(*aes_crypto_cmd)(AesOption option, void* input,
		void* output, unsigned int size, AesMode mode,
		void* iv, void* key);

unsigned int aes_decrypt_key(unsigned char* in, unsigned char** out);
unsigned int aes_encrypt_key(unsigned char* in, unsigned char** out);

#endif /* AES_H */
