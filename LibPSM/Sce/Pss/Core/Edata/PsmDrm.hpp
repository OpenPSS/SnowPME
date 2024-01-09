#ifndef LIB_PSS_PSM_DRM_H
#define LIB_PSS_PSM_DRM_H 1
#include <Sce/Pss/Core/Edata/PsmDrmLicense.hpp>

namespace Sce::Pss::Core::Edata {
	class PsmDrm {
	private:
	public:
		static int scePsmDrmGetRifKey(const ScePsmDrmLicense* license_buf, char* keydata, int flags);
	};
}
#endif