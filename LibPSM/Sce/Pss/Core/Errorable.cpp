#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core {
	Errorable::Errorable() {

	}
	Errorable::~Errorable() {

	}

	uint32_t Errorable::SetError(uint32_t error) {
		this->lastError = error;
		return error;
	}
	uint32_t Errorable::GetError() {
		return this->lastError;
	}
}