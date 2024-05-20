#include <Callback/Impl.hpp>
#include <stdexcept>
namespace SnowPME::Callback {
	bool Impl::isInitalized = false;
	void Impl::ErrorOnNotInit() {
		if (!Impl::isInitalized) {
			throw std::runtime_error("GraphicsWindowImpl is not initalized!");
		}
	}
}
