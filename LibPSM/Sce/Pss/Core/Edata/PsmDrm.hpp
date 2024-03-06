#ifndef LIB_PSS_PSM_DRM_H
#define LIB_PSS_PSM_DRM_H 1
#include <Sce/Pss/Core/Edata/PsmDrmLicense.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

#include <string>
#include <iostream>

namespace Sce::Pss::Core::Edata {
	static const std::string FakeRifLocation = "/Application/FAKE.rif";

	class PsmDrm : public Errorable {
	private:
		std::string psmContentId;
		uint8_t titleKey[0x10];
	public:
		PsmDrm(std::string licenseFile);
		PsmDrm(std::string contentId, uint8_t* titleKey);
		std::string GetContentId();
		void GetTitleKey(uint8_t* outTitleKey);
	};
}
#endif