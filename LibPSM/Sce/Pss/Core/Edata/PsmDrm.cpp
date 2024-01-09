#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Edata {
	int PsmDrm::scePsmDrmGetRifKey(const ScePsmDrmLicense* license_buf, char* keydata, int flags) {

		memcpy(keydata, license_buf->Key, sizeof(ScePsmDrmLicense::Key));

		return PSM_ERROR_NO_ERROR;
	}
}