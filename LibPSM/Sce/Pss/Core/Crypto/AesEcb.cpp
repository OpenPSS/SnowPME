#include <Sce/Pss/Core/Crypto/AesEcb.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
#include <stdexcept>

namespace Sce::Pss::Core::Crypto {

	AesEcb::AesEcb(uint8_t key[0x10]) {
		AES_init_ctx(&this->ctx, key);
	}

	void AesEcb::Decrypt(uint8_t* data, uint32_t dataSize) {
		if (dataSize % AES_BLOCKLEN != 0)
			throw std::runtime_error("dataSize not aligned to aes block size.");

		for(int i = 0; i < dataSize / AES_BLOCKLEN; i++)
			AES_ECB_decrypt(&this->ctx, data + (i * AES_BLOCKLEN));
	}

	void AesEcb::Decrypt(std::vector<uint8_t>& data) {
		if (data.size() % AES_BLOCKLEN != 0)
			throw std::runtime_error("dataSize not aligned to aes block size.");

		for (int i = 0; i < data.size() / AES_BLOCKLEN; i++)
			AES_ECB_decrypt(&this->ctx, data.data() + (i * AES_BLOCKLEN));
	}
}
