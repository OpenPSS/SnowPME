#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core {

	uint32_t Errorable::SetError(uint32_t error) {
		this->lastError = error;
		return error;
	}
	uint32_t Errorable::GetError() {
		return this->lastError;
	}

	uint32_t Errorable::GetClearError() {
		uint32_t err = this->GetError();
		this->SetError(PSM_ERROR_NO_ERROR);
		return err;
	}

}