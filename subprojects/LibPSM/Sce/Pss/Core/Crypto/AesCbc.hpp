#ifndef LIB_PSS_AESCBC_H
#define LIB_PSS_AESCBC_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
namespace Sce::Pss::Core::Crypto {
	class AesCbc {
	private:
		aes128_key ctx_dec;
		uint8_t iv[0x10];
	public:
		AesCbc(uint8_t key[0x10], uint8_t iv[0x10]);
		void SetIv(uint8_t iv[0x10]);
		void Decrypt(uint8_t* data, uint32_t dataSize);
		void Decrypt(std::vector<uint8_t>& data);
	};
}

#endif