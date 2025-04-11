#include <Sce/Pss/Core/Crypto/AesCbc.hpp>
#include <Sce/Pss/Core/Crypto/Algorithms/Algorithms.hpp>

namespace Sce::Pss::Core::Crypto {

	AesCbc::AesCbc(uint8_t key[0x10], uint8_t iv[0x10]) {
		AES_init_ctx_iv(&this->ctx, key, iv);
	}

	void AesCbc::SetIv(uint8_t iv[0x10]) {
		AES_ctx_set_iv(&this->ctx, iv);
	}
	
	void AesCbc::Decrypt(uint8_t* data, uint32_t dataSize) {
		AES_CBC_decrypt_buffer(&this->ctx, data, dataSize);
	}

	void AesCbc::Decrypt(std::vector<uint8_t>& data) {
		AES_CBC_decrypt_buffer(&this->ctx, data.data(), data.size());
	}
}