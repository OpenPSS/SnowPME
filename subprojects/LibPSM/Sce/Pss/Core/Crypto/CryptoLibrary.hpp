#ifndef LIB_PSS_CRYPTOLIBRARY_H 
#define LIB_PSS_CRYPTOLIBRARY_H
#include <vector>
#include <stdint.h>
#include <stddef.h>


namespace Sce::Pss::Core::Crypto {
	class CryptoLibrary {
	public:
		static const int AesBlockSize = 0x10;
		static const int Md5HashSize = 0x10;
		static void HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], uint8_t* in, size_t insize);
		static void HmacSha256(const uint8_t key[0x20], uint8_t out[0x20], std::vector<uint8_t> in);

		static void Md5Sum(uint8_t* data, const size_t datasize, uint8_t md5[0x10]);
		static void Sha256Sum(uint8_t* data, const uint32_t datasize, uint8_t sha[0x20]);
		static void Sha1Sum(uint8_t* data, const uint32_t datasize, uint8_t sha[0x14]);

		static void Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize);
		static void Aes128CbcEncrypt(const uint8_t key[0x10], const uint8_t iv[0x10], std::vector<uint8_t>& in, std::vector<uint8_t>& out);
		static void Aes128CbcDecrypt(const uint8_t key[0x10], const uint8_t iv[0x10], uint8_t* data, size_t datasize);
	};
}

#endif
