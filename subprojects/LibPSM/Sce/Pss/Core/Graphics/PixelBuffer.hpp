#ifndef LIB_PSS_PIXELBUFFER
#define LIB_PSS_PIXELBUFFER 1

#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	class PixelBuffer : public GraphicsObject<PixelBuffer> {
	private:
		static uint8_t formatProperties[];
	protected:
		std::string filename = "";
		PixelBufferType type = PixelBufferType::None;
		int width = 0;
		int height = 0;
		int level = 0;
		int unk11 = 0;
		GLenum glPixelBufferType;
		PixelFormat format = PixelFormat::None;
		PixelBufferOption option = PixelBufferOption::None;

	public:
		PixelBuffer() = default;
		~PixelBuffer() = default;
		uint32_t SetError(int errorCode);
		bool GetFormatIsValid(PixelFormat format);
		bool CheckFormatError(PixelFormat format, PixelBufferOption option);
		bool CheckSizeError(int width, int height, int min, int max);
		bool CheckFormatSizeError(PixelFormat format, int width, int height);
		int GetFormatHasDepth(PixelFormat format);
		int GetFormatHasRgb(PixelFormat format);
		int GetFormatHasHalfFloat(PixelFormat format);
		int CalculateTotalMipMaps(int width, int height);
		GLenum GLPixelBufferType();

		int LoadFile(const char* fileName, uint8_t* &fileData, uint32_t &fileSize);
		int LoadImage(uint8_t* data, uint64_t dataLen, int mipmap, PixelFormat format);
		int GetInfo(PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option);
	};
}
#endif