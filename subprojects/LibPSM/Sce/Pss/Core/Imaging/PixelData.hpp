#ifndef LIB_PSS_PIXELDATA_H
#define LIB_PSS_PIXELDATA_H 1
#include <cstdint>

namespace Sce::Pss::Core::Imaging {
	class PixelData {
	public:
		uint8_t* data;
		uint32_t size;
	};
}

#endif