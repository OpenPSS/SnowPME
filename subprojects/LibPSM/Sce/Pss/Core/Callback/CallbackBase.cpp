#include <Sce/Pss/Core/Callback/CallbackBase.hpp>
#include <stdexcept>

namespace Sce::Pss::Core::Callback {

	bool CallbackBase::isInitalized = false;

	void CallbackBase::errorOnNotInitalized() {
		if (CallbackBase::isInitalized == false) {
			throw std::runtime_error("CallbackBase is not initalized,");
		}
	}

}