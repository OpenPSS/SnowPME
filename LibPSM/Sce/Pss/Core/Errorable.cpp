#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core {
	Errorable::Errorable() {

	}
	Errorable::~Errorable() {

	}

	void Errorable::SetError(uint32_t error) {
		this->lastError = error;
	}
	uint32_t Errorable::GetError() {
		return this->lastError;
	}
}