#include <Sce/Pss/Core/Callback/Callbacks.hpp>
#include <exception>

namespace Sce::Pss::Core::Callback {

	bool Callbacks::isInitalized = false;

	void Callbacks::errorOnNotInitalized() {
		if (Callbacks::isInitalized == false) {
			throw std::exception("AudioCallbacks is not initalized,");
		}
	}

}