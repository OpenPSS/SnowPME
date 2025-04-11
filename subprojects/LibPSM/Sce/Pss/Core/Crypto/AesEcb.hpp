#ifndef LIB_PSS_AES_H
#define LIB_PSS_AES_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
namespace Sce::Pss::Core::Crypto {
	class AesEcb {
	private:
		struct AES_ctx ctx;
	public:
		AesEcb(uint8_t key[0x10]);
		void Decrypt(uint8_t* data, uint32_t dataSize);
		void Decrypt(std::vector<uint8_t>& data);
	};
}

#endif