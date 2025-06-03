#include <Sce/Pss/Core/Services/AccountInformation.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Services/UniqueId.hpp>

#include <LibShared.hpp>

#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Services;
using namespace Sce::Pss::Core::Mono;


namespace Sce::Pss::Core::Services {

	int AccountInformation::GetUniqueID(MonoArray* id) {
		Logger::Debug(__FUNCTION__);

		if (id == NULL)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		
		uint8_t* idBuffer = (uint8_t*)mono_array_addr_with_size(id, 1, 0);
		int idLen = MonoUtil::MonoArrayBytesLength(id);

		if (idLen != 0x10)
			return PSM_ERROR_COMMON_INVALID_OPERATION;

		return UniqueId::GetUniqueIDForEmulatedPlatform(idBuffer);
	}
}
