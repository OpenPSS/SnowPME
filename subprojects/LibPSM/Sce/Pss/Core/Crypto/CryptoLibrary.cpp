#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
#include <stdexcept>

namespace Sce::Pss::Core::Crypto {
	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], uint8_t* in, size_t insize) {
		hmac_sha256(key, SHA256_HASH_SIZE, in, insize, out, SHA256_HASH_SIZE);
	}

	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], std::vector<uint8_t> in) {
		hmac_sha256(key, SHA256_HASH_SIZE, in.data(), in.size(), out, SHA256_HASH_SIZE);
	}

	void CryptoLibrary::Sha1Sum(uint8_t* data, const uint32_t datasize, uint8_t sha[0x14]) {
		SHA1_CTX ctx;
		SHA1Init(&ctx);
		SHA1Update(&ctx, data, datasize);
		SHA1Final(sha, &ctx);
	}

	void CryptoLibrary::Sha256Sum(uint8_t* data, const uint32_t datasize, uint8_t sha[0x20]) {
		SHA256_HASH shaHash;
		Sha256Calculate(data, datasize, &shaHash);
		memcpy(sha, shaHash.bytes, sizeof(shaHash.bytes));
	}

	void CryptoLibrary::Md5Sum(uint8_t* data, const size_t datasize, uint8_t md5[0x10]) {
		MD5Context context;
		md5Init(&context);
		md5Update(&context, data, datasize);
		md5Finalize(&context);
		
		memcpy(md5, context.digest, CryptoLibrary::Md5HashSize);
	}


	void CryptoLibrary::Aes128CbcDecrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize) {
		if (datasize % AES_BLOCKLEN != 0)
			throw std::runtime_error("data is not aligned to block size.");

		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, key, iv);
		AES_CBC_decrypt_buffer(&ctx, data, datasize);
	}

	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize) {
		if (datasize % AES_BLOCKLEN != 0)
			throw std::runtime_error("data is not aligned to block size.");

		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, key, iv);
		AES_CBC_encrypt_buffer(&ctx, data, datasize);
	}
	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], std::vector<uint8_t>& in, std::vector<uint8_t>& out) {
		struct AES_ctx ctx;
		AES_init_ctx_iv(&ctx, key, iv);

		out = std::vector<uint8_t>(AES_BLOCKLEN - (in.size() % AES_BLOCKLEN));
		memcpy(out.data(), in.data(), in.size());

		AES_CBC_encrypt_buffer(&ctx, out.data(), out.size());
	}

}
