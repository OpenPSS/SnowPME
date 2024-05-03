#include <Sce/Pss/Core/Services/UniqueId.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>

#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <Sce/Pss/Core/Crypto/Keys.hpp>

#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <cstring>


namespace Sce::Pss::Core::Services {
	using namespace Shared::Debug;
	
	int UniqueId::getUniqueIDWindows(uint8_t* id) {
		std::string username = Shared::Config::Username;

		size_t length = username.length();
		
		if (length > 0x10)
			length = 0x10;

		std::memcpy(id, username.c_str(), length);

		return PSM_ERROR_NO_ERROR;
	}
	int UniqueId::getUniqueIDAndroid(uint8_t* id) {
		return UniqueId::getUniqueIDVita(id);
	}
	int UniqueId::getUniqueIDVita(uint8_t* id) {
		uint8_t outhmac[0x20];
		uint64_t accountId = Shared::Config::AccountId;
		
		Crypto::CryptoLibrary::HmacSha256(Crypto::Keys::HashAccountIdHmac256, outhmac, (uint8_t*)&accountId, sizeof(uint64_t));
		
		uint64_t hashid[2];
		hashid[0] = accountId;
		hashid[1] = ((uint64_t*)outhmac)[0];

		Crypto::CryptoLibrary::Aes128CbcEncrypt(Crypto::Keys::HashAccountIdAes128, Crypto::Keys::NullIv, (uint8_t*)hashid, 0x10);
		std::memcpy(id, hashid, 0x10);

		return PSM_ERROR_NO_ERROR;
	}
	int UniqueId::GetUniqueIDForEmulatedPlatform(uint8_t* id) {		
		// clear id
		std::memset(id, 0x00, 0x10);

		switch (Shared::Config::TargetImplementation) {
		case Shared::RuntimeImplementation::PSVita:
			return getUniqueIDVita(id);
		case Shared::RuntimeImplementation::Android:
			return getUniqueIDAndroid(id);
		case Shared::RuntimeImplementation::Windows:
		default:
			return getUniqueIDWindows(id);

		}
	}

}
