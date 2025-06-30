#ifndef LIB_PSS_PIXELBUFFER
#define LIB_PSS_PIXELBUFFER 1

#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>

namespace Sce::Pss::Core::Graphics {
	class PixelBuffer : public GraphicsObject{
	private:
		PixelBufferType type = PixelBufferType::None;
		int width = 0;
		int height = 0;
		int level = 0;
		PixelFormat format = PixelFormat::None;
		PixelBufferOption option = PixelBufferOption::None;

	public:
		PixelBuffer();
		~PixelBuffer();
		int LoadFile(const char* fileName, uint8_t* &fileData, uint32_t &fileSize);
		int LoadImage(char* data, uint64_t dataLen, int mipmap, PixelFormat format);
		int GetInfo(PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option);
	};
}
#endif