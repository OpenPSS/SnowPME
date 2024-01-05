#include <Callback/Impl.hpp>
#include <exception>
namespace SnowPME::Callback {
	bool Impl::isInitalized = false;
	void Impl::ErrorOnNotInit() {
		if (!Impl::isInitalized) {
			throw std::exception("GraphicsWindowImpl is not initalized!");
		}
	}
}