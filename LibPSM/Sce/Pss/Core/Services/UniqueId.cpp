#include <Sce/Pss/Core/Services/UniqueId.hpp>
#include <Sce/Pss/Core/PlatformSpecific.hpp>

#include <Sce/PlayStation/Core/Error.hpp>
#include <LibShared.hpp>
namespace Sce::Pss::Core::Services {
	
	int UniqueId::getUniqueIDWindows(std::byte* id) {
		std::string username = PlatformSpecific::Username();
		size_t length = username.length();
		
		if (length > 0x10)
			length = 0x10;

		memcpy(id, username.c_str(), length);

		return PSM_ERROR_NO_ERROR;
	}
	int UniqueId::getUniqueIDAndroid(std::byte* id) {
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int UniqueId::getUniqueIDVita(std::byte* id) {
		return PSM_ERROR_NOT_IMPLEMENTED;
	}
	int UniqueId::GetUniqueIDForEmulatedPlatform(std::byte* id) {
		Shared::RuntimeImplementation impl = Shared::Config::GetRuntimeImplementation();
		
		// clear id
		memset(id, 0x00, 0x10);

		switch (impl) {
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