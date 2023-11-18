#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>

extern "C" {
#define CBC 1
#define CTR 1
#define ECB 1

#include "Algorithms/aes.h"
#include "Algorithms/hmac_sha256.h"
#include "Algorithms/sha256.h"
}

namespace Sce::Pss::Core::Crypto {
	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], uint8_t* in, size_t insize) {
		hmac_sha256(key, SHA256_HASH_SIZE, in, insize, out, SHA256_HASH_SIZE);
	}

	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], std::vector<uint8_t> in) {
		hmac_sha256(key, SHA256_HASH_SIZE, in.data(), in.size(), out, SHA256_HASH_SIZE);
	}
	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize) {
		if (datasize % AES_BLOCKLEN != 0)
			throw std::exception("data is not aligned to block size.");

		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, key, iv);
		AES_CBC_encrypt_buffer(&ctx, data, datasize);
	}
	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], std::vector<uint8_t> in, std::vector<uint8_t>& out) {
		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, key, iv);

		out = std::vector<uint8_t>(AES_BLOCKLEN - (in.size() % AES_BLOCKLEN));
		memcpy(out.data(), in.data(), in.size());

		AES_CBC_encrypt_buffer(&ctx, out.data(), out.size());
	}

}