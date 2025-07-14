#include <Debug/Assert.hpp>
#include <Windowing/CallbackBase.hpp>

namespace Shared::Windowing {

	bool CallbackBase::isInitalized = false;

	void CallbackBase::errorOnNotInitalized() {
		ASSERT(CallbackBase::isInitalized == true);
	}

	bool CallbackBase::IsInitalized() {
		return CallbackBase::isInitalized;
	}
}