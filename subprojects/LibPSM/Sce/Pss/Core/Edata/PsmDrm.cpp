#include <Sce/Pss/Core/Edata/PsmDrm.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <LibShared.hpp>
#include <string.h>

namespace Sce::Pss::Core::Edata {
	using namespace Sce::Pss::Core::Io;
	using namespace Shared::Debug;

	PsmDrm::PsmDrm(const std::string& licenseFile) {
		uint64_t handle = -1;
		ScePsmDrmLicense rifData;
		uint32_t wasRead = 0;
		Logger::Debug("Reading FAKE.rif ...");

		int err = ICall::PsmFileOpenSystem((char*)licenseFile.c_str(), SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle, true);
		if (err == PSM_ERROR_NO_ERROR) {
			err = ICall::PsmFileRead(handle, &rifData, sizeof(ScePsmDrmLicense), &wasRead);
			
			if (err == PSM_ERROR_NO_ERROR) {
				this->psmContentId = std::string(rifData.ContentId, sizeof(rifData.ContentId));
				memcpy(this->titleKey, rifData.Key, sizeof(this->titleKey));

				Logger::Debug("RIF Content ID: " + this->psmContentId);

			}
			else {
				this->SetError(err);
			}

			ICall::PsmClose(handle);
		}
		else {
			this->SetError(err);
		}
	}

	PsmDrm::PsmDrm(const std::string& contentId, uint8_t* titleKey) {
		this->psmContentId = contentId;
		memcpy(this->titleKey, titleKey, sizeof(this->titleKey));
	}
	

	const std::string& PsmDrm::GetContentId() {
		return this->psmContentId;
	}

	void PsmDrm::GetTitleKey(uint8_t* outTitleKey) {
		memcpy(outTitleKey, this->titleKey, sizeof(this->titleKey));
	}

}
