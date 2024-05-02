#include <Sce/Pss/Core/Callback/Callbacks.hpp>
#include <stdexcept>

namespace Sce::Pss::Core::Callback {

	bool Callbacks::isInitalized = false;

	void Callbacks::errorOnNotInitalized() {
		if (Callbacks::isInitalized == false) {
			throw std::runtime_error("AudioCallbacks is not initalized,");
		}
	}

}
