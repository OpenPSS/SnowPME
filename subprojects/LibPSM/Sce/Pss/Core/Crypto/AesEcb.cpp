#include <Sce/Pss/Core/Crypto/AesEcb.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core::Crypto {

	AesEcb::AesEcb(uint8_t key[0x10]) {
		aes128_init_dec(&this->ctx_dec, key);
	}

	void AesEcb::Decrypt(uint8_t* data, uint32_t dataSize) {
		ASSERT(dataSize % AES_BLOCKLEN == 0);
		aes128_ecb_encrypt(&this->ctx_dec, data, dataSize);
	}

	void AesEcb::Decrypt(std::vector<uint8_t>& data) {
		this->Decrypt(data.data(), data.size());
	}
}
