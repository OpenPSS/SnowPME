#ifndef LIB_PSM_CLEARMASK_H
#define LIB_PSM_CLEARMASK_H
#include <string>

namespace Sce::PlayStation::Core::Graphics {
	enum class ClearMask : unsigned int {
		None = 0,
		Color = 1,
		Depth = 2,
		Stencil = 4,
		All = 7
	};

	ClearMask operator&(ClearMask l, ClearMask r);
	ClearMask operator&(ClearMask l, unsigned int r);
	ClearMask operator&(unsigned int l, ClearMask r);

	ClearMask operator|(ClearMask l, ClearMask r);
	ClearMask operator|(unsigned int l, ClearMask r);
	ClearMask operator|(ClearMask l, unsigned int r);

}

#endif