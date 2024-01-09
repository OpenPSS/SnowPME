#ifndef LIB_PSS_CRYPTOLIBRARY_H 
#define LIB_PSS_CRYPTOLIBRARY_H
#include <vector>

namespace Sce::Pss::Core::Crypto {
	class CryptoLibrary {
	public:
		static void HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], uint8_t* in, size_t insize);
		static void HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], std::vector<uint8_t> in);
		static void Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize);
		static void Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], std::vector<uint8_t> in, std::vector<uint8_t>& out);

		static void Aes128CbcDecrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize);
		static void Aes256CbcDecrypt(const uint8_t key[0x20], const uint8_t iv[0x10], uint8_t* data, size_t datasize);

	};
}

#endif