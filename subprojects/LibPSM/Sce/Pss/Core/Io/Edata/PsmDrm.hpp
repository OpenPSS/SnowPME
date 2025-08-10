#ifndef LIB_PSS_PSM_DRM_H
#define LIB_PSS_PSM_DRM_H 1
#include <Sce/Pss/Core/Io/Edata/PsmDrmLicense.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

#include <string>
#include <iostream>

namespace Sce::Pss::Core::Io::Edata {
	static const std::string FakeRifLocation = "/License/FAKE.rif";

	class PsmDrm : public Errorable {
	private:
		std::string psmContentId = "";
		uint8_t klicensee[0x10] = { 0 };
	public:
		PsmDrm(const std::string& licenseFile);
		PsmDrm(const std::string& contentId, uint8_t klicensee[0x10]);
		const std::string& GetContentId();
		uint8_t* GetKlicensee();
	};
}
#endif