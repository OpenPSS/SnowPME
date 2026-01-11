#ifndef LIB_PSS_PIXELBUFFER
#define LIB_PSS_PIXELBUFFER 1

#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/PixelFormat.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferType.hpp>
#include <Sce/Pss/Core/Graphics/PixelBufferOption.hpp>
#include <Sce/Pss/Core/Graphics/InternalOption.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Graphics/TextureCubeFace.hpp>

#include <glad/glad.h>

#define IS_POW_2(x) (((x - 1) & x) == 0)

namespace Sce::Pss::Core::Graphics {
	class PixelBuffer : public GraphicsObject<PixelBuffer> {
	private:
		static uint8_t formatProperties[];
		static uint8_t formatBpp[];
	protected:
		std::string filename = "";
		PixelBufferType type = PixelBufferType::None;
		int width = 0;
		int height = 0;
		int mipmapLevel = 0;
		int unk11 = 0;
		bool needsHalfFloat = false;
		bool npot = false;

		size_t imageSize = 0;

		GLenum glPixelBufferType;
	public:
		PixelFormat Format = PixelFormat::None;
		PixelBufferOption Option = PixelBufferOption::None;


		PixelBuffer() = default;
		~PixelBuffer() = default;
		uint32_t SetError(int errorCode);
		bool GetFormatIsValid(PixelFormat format);
		bool CheckFormatError(PixelFormat format, PixelBufferOption option);
		bool CheckSizeError(int width, int height, int min, int max);
		bool CheckFormatSizeError(PixelFormat format, int width, int height);
		bool CheckGLError();
		bool AllocCache(InternalOption opt);
		int GetMipmapWidth(int level);
		int GetMipmapHeight(int level);

		GLenum GLPixelBufferType();
		GLenum GetDeviceFaceTarget(TextureCubeFace face);

		static bool GetFormatHasDepth(PixelFormat format);
		static bool GetFormatHasRgb(PixelFormat format);
		static bool GetFormatHasHalfFloat(PixelFormat format);
		static int GetFormatBitsPerPixel(PixelFormat format);
		static int CalculateTotalMipMaps(int width, int height);
		static bool CheckPowerOfTwo(int width, int height);
		
		static bool IsFormatDxt(PixelFormat format);
		static int AdjValueForDxt(bool isDxt, int v);
		static int CalculateImageArraySizeInBytes(PixelFormat format, int bitsPerPixel, int width, int height);


		int LoadFile(const char* fileName, uint8_t*& fileData, uint32_t& fileSize);
		int LoadImage(uint8_t* data, uint64_t dataLen, int mipmap, PixelFormat format);
		int GetInfo(PixelBufferType* type, int* width, int* height, int* level, PixelFormat* format, PixelBufferOption* option);
	};
}
#endif