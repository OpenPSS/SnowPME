#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>


#if defined(_MSC_VER)
#  define NORETURN __declspec(noreturn)
#  define PKG_ALIGN(x) __declspec(align(x))
#else
#  define NORETURN __attribute__((noreturn))
#  define PKG_ALIGN(x) __attribute__((aligned(x)))
#endif

#define AES_BLOCKLEN (16)

typedef struct aes128_key {
    uint32_t PKG_ALIGN(16) key[44];
} aes128_key;

void aes128_init(aes128_key* ctx, const uint8_t* key);
void aes128_init_dec(aes128_key* ctx, const uint8_t* key);

void aes128_ecb_encrypt(const aes128_key* ctx, uint8_t* data, size_t size);
void aes128_ecb_decrypt(const aes128_key* ctx, uint8_t* data, size_t size);

void aes128_cbc_encrypt(const aes128_key* ctx, const uint8_t* iv, uint8_t* buffer, size_t size);
void aes128_cbc_decrypt(const aes128_key* ctx, const uint8_t* iv, uint8_t* buffer, size_t size);

void aes128_ctr_xor(const aes128_key* ctx, const uint8_t* iv, uint64_t block, uint8_t* buffer, size_t size);

void aes128_cmac(const uint8_t* key, const uint8_t* buffer, uint32_t size, uint8_t* mac);

#ifdef __cplusplus
}
#endif