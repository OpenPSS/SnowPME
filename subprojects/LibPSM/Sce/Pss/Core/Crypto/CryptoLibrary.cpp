#include <LibShared.hpp>
#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Crypto {
	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], const uint8_t* in, size_t insize) {
		hmac_sha256(key, SHA256_HASH_SIZE, in, insize, out, SHA256_HASH_SIZE);
	}

	void CryptoLibrary::HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], std::vector<uint8_t>& in) {
		hmac_sha256(key, SHA256_HASH_SIZE, in.data(), in.size(), out, SHA256_HASH_SIZE);
	}

	void CryptoLibrary::Sha1Sum(const uint8_t* data, const size_t datasize, uint8_t sha[0x14]) {
		SHA1_CTX ctx;
		SHA1Init(&ctx);
		SHA1Update(&ctx, data, datasize);
		SHA1Final(sha, &ctx);
	}

	void CryptoLibrary::Sha256Sum(const uint8_t* data, const size_t datasize, uint8_t sha[0x20]) {
		SHA256_HASH shaHash;
		Sha256Calculate(data, datasize, &shaHash);
		memcpy(sha, shaHash.bytes, sizeof(shaHash.bytes));
	}

	void CryptoLibrary::Md5Sum(const uint8_t* data, const size_t datasize, uint8_t md5[0x10]) {
		MD5Context context;
		md5Init(&context);
		md5Update(&context, data, datasize);
		md5Finalize(&context);
		
		memcpy(md5, context.digest, CryptoLibrary::Md5HashSize);
	}


	void CryptoLibrary::Aes128CbcDecrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize) {
		ASSERT(datasize % AES_BLOCKLEN == 0);

		aes128_key ctx;
		aes128_init_dec(&ctx, key);
		aes128_cbc_decrypt(&ctx, iv, data, datasize);

	}

	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize) {
		ASSERT(datasize % AES_BLOCKLEN == 0);

		aes128_key ctx;
		aes128_init(&ctx, key);
		aes128_cbc_encrypt(&ctx, iv, data, datasize);
	}
	void CryptoLibrary::Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], std::vector<uint8_t>& in, std::vector<uint8_t>& out) {
		out = std::vector<uint8_t>(in.size() + (AES_BLOCKLEN - (in.size() % AES_BLOCKLEN)));
		memcpy(out.data(), in.data(), in.size());

		aes128_key ctx;
		aes128_init(&ctx, key);
		aes128_cbc_encrypt(&ctx, iv, out.data(), out.size());
		out.resize(in.size());
	}

}
