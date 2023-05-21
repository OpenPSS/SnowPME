#include <Sce/PlayStation/Core/Graphics/ColorMask.hpp>

namespace Sce::PlayStation::Core::Graphics {
	ColorMask operator&(ColorMask l, ColorMask r) { return (ColorMask)((uint8_t)l & (uint8_t)r); };
	ColorMask operator&(ColorMask l, uint8_t r) { return (ColorMask)((uint8_t)l & (uint8_t)r); };
	ColorMask operator&(uint8_t l, ColorMask r) { return (ColorMask)((uint8_t)l & (uint8_t)r); };

	ColorMask operator|(ColorMask l, ColorMask r) { return (ColorMask)((uint8_t)l | (uint8_t)r); };
	ColorMask operator|(uint8_t l, ColorMask r) { return (ColorMask)((uint8_t)l | (uint8_t)r); };
	ColorMask operator|(ColorMask l, uint8_t r) { return (ColorMask)((uint8_t)l | (uint8_t)r); };
}