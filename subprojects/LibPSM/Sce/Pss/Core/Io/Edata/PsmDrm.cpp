#include <Sce/Pss/Core/Io/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <LibShared.hpp>
#include <string.h>

using namespace Sce::Pss::Core::Io;
using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core::Io::Edata {


	PsmDrm::PsmDrm(const std::string& licenseFile) {
		ScePsmDrmLicense rifData;
		Logger::Debug("[PsmDrm] Reading license [" + licenseFile + "] ...");
		std::fstream licenseStream(licenseFile, std::ios::in | std::ios::binary);
		
		if (!licenseStream.fail()) {
			uint64_t rd = licenseStream.read(reinterpret_cast<char*>(&rifData), sizeof(ScePsmDrmLicense)).gcount();
			if (rd == sizeof(ScePsmDrmLicense)) {
				this->psmContentId = std::string(rifData.ContentId, sizeof(rifData.ContentId));
				memcpy(this->klicensee, rifData.Key, sizeof(this->klicensee));
				Logger::Debug("[PsmDrm] RIF Content ID: " + this->psmContentId);
			}
			else {
				Logger::Error("[PsmDrm] license was only: 0x" + Format::Hex(rd) + "bytes but expected 0x" + Format::Hex(sizeof(ScePsmDrmLicense)) + " bytes");
				this->SetError(PSM_ERROR_COMMON_IO);
			}
		}
		else {
			Logger::Error("[PsmDrm] Failed to open file " + Format::Hex(errno) + " - " + strerror(errno));
			this->SetError(PSM_ERROR_COMMON_IO);
		}
		
	}

	PsmDrm::PsmDrm(const std::string& contentId, uint8_t klicensee[0x10]) {
		this->psmContentId = contentId;
		memcpy(this->klicensee, klicensee, sizeof(this->klicensee));
	}
	

	const std::string& PsmDrm::GetContentId() {
		return this->psmContentId;
	}

	uint8_t* PsmDrm::GetKlicensee() {
		return this->klicensee;
	}
}
