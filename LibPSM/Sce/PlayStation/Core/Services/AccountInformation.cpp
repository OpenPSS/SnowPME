#include <Sce/PlayStation/Core/Services/AccountInformation.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

#include <Sce/Pss/Core/Mono/Util.hpp>
#include <Sce/Pss/Core/Services/UniqueId.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>
using namespace Shared::Debug;

namespace Sce::PlayStation::Core::Services {
	int AccountInformation::GetUniqueID(MonoArray* id) {
		Logger::Debug(__FUNCTION__);

		if (id == NULL)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		
		std::byte* idBuffer = (std::byte*)mono_array_addr_with_size(id, 1, 0);
		int idLen = Sce::Pss::Core::Mono::Util::MonoArrayLength(id);

		if (idLen != 0x10)
			return PSM_ERROR_COMMON_INVALID_OPERATION;

		return Sce::Pss::Core::Services::UniqueId::GetUniqueIDForEmulatedPlatform(idBuffer);
	}
}
