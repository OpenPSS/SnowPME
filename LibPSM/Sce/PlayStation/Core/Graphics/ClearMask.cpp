#include <Sce/PlayStation/Core/Graphics/ClearMask.hpp>

namespace Sce::PlayStation::Core::Graphics {
	ClearMask operator&(ClearMask l, ClearMask r) { return (ClearMask)((unsigned int)l & (unsigned int)r); };
	ClearMask operator&(ClearMask l, unsigned int r) { return (ClearMask)((unsigned int)l & (unsigned int)r); };
	ClearMask operator&(unsigned int l, ClearMask r) { return (ClearMask)((unsigned int)l & (unsigned int)r); };

	ClearMask operator|(ClearMask l, ClearMask r) { return (ClearMask)((unsigned int)l | (unsigned int)r); };
	ClearMask operator|(unsigned int l, ClearMask r) { return (ClearMask)((unsigned int)l | (unsigned int)r); };
	ClearMask operator|(ClearMask l, unsigned int r) { return (ClearMask)((unsigned int)l | (unsigned int)r); };
}