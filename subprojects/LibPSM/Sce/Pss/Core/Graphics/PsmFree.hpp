#ifndef LIB_PSS_PSMFREE_H
#define LIB_PSS_PSMFREE_H 1

#include <stdint.h>
#include <Sce/Pss/Core/Graphics/PsmObjectType.hpp>

namespace Sce::Pss::Core::Graphics {
	class PsmFree {
	private:
		PsmObjectType type;
		int handle = 0;
	public:
		PsmObjectType Type();
		int Handle();

		PsmFree(PsmObjectType action, int handle);
		PsmFree() = default;
		~PsmFree() = default;
	};
}

#endif