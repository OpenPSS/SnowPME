#include <Sce/Pss/Core/Crypto/AesCbc.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>

namespace Sce::Pss::Core::Crypto {

	AesCbc::AesCbc(uint8_t key[0x10], uint8_t iv[0x10]) {
		aes128_init(&this->ctx_dec, key);
		memcpy(this->iv, iv, sizeof(this->iv));
	}

	void AesCbc::SetIv(uint8_t iv[0x10]) {
		memcpy(this->iv, iv, sizeof(this->iv));
	}
	
	void AesCbc::Decrypt(uint8_t* data, uint32_t dataSize) {
		aes128_cbc_decrypt(&this->ctx_dec, this->iv, data, dataSize);
	}

	void AesCbc::Decrypt(std::vector<uint8_t>& data) {
		aes128_cbc_decrypt(&this->ctx_dec, this->iv, data.data(), data.size());
	}
}