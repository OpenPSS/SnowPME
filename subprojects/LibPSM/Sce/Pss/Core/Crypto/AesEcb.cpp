#include <Sce/Pss/Core/Crypto/AesEcb.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
#include <stdexcept>

namespace Sce::Pss::Core::Crypto {

	AesEcb::AesEcb(uint8_t key[0x10]) {
		aes128_init_dec(&this->ctx_dec, key);
	}

	void AesEcb::Decrypt(uint8_t* data, uint32_t dataSize) {
		if (dataSize % AES_BLOCKLEN != 0)
			throw std::runtime_error("dataSize not aligned to aes block size.");
		aes128_ecb_encrypt(&this->ctx_dec, data, dataSize);
	}

	void AesEcb::Decrypt(std::vector<uint8_t>& data) {
		if (data.size() % AES_BLOCKLEN != 0)
			throw std::runtime_error("dataSize not aligned to aes block size.");
		aes128_ecb_decrypt(&this->ctx_dec, data.data(), data.size());
	}
}
