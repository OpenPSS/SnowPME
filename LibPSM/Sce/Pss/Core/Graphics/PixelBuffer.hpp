#ifndef LIB_PSS_PIXELBUFFER
#define LIB_PSS_PIXELBUFFER 1
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>

namespace Sce::Pss::Core::Graphics {
	class PixelBuffer : public GraphicsObject {
	public:
		PixelBuffer();
		~PixelBuffer();
		int LoadFile(const char* fileName, uint8_t* &fileData, uint32_t &fileSize);
	};
}
#endif