#ifndef LIB_PSS_PSM_DRM_H
#define LIB_PSS_PSM_DRM_H 1
#include <Sce/Pss/Core/Edata/PsmDrmLicense.hpp>
#include <Sce/Pss/Core/Io/FileSystem.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <string>
#include <iostream>

namespace Sce::Pss::Core::Edata {
	class PsmDrm : public Errorable {
	private:
		std::string contentId;
		std::byte titleKey[0x10];
	public:
		PsmDrm(std::string licenseFile);
		PsmDrm(std::string contentId, std::byte* titleKey);
		std::string GetContentId();
		void GetTitleKey(std::byte* outTitleKey);
	};
}
#endif