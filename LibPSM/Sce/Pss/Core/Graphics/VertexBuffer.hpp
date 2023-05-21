#ifndef LIB_PSM_VERTEXBUFFER_H
#define LIB_PSM_VERTEXBUFFER_H 1
#include <cstdint>
#include <vector>
#include <Sce/PlayStation/Core/Vector4.hpp>
#include <Sce/PlayStation/Core/Graphics/ElementType.hpp>
#include <Sce/PlayStation/Core/Graphics/VertexFormat.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>

using namespace Sce::PlayStation::Core::Graphics;
using namespace Sce::PlayStation::Core;

namespace Sce::Pss::Core::Graphics {

	typedef uint16_t half;
	typedef int8_t byte;
	typedef uint8_t ubyte;

	class VertexBuffer : public GraphicsObject {
	private:
		int vertexCount = 0;
		int indexCount = 0;
		int instDivisor = 0;
		int option = 0;
		size_t size = 0;
		std::vector<VertexFormat>* vertexFormats = NULL;
		bool translationScaleNormalize(VertexFormat inputFormat, VertexFormat* outputFormat, Vector4** trans, Vector4** scale);
	public:
		VertexBuffer(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* vertexFormats, int vertexFormatsLen);
		~VertexBuffer();
		static bool GetFormatIsValid(VertexFormat format);
		static ElementType GetFormatElementType(VertexFormat format);
		static int GetFormatVectorHeight(VertexFormat format);
		static int GetFormatVectorWidth(VertexFormat format);
		static int GetFormatVectorSize(VertexFormat format);
		static bool GetFormatElementNormalize(VertexFormat format);
		static int GetFormatElementSize(VertexFormat format);
		int ActiveStateChanged(bool state);
		int VertexCount();
		int SetVerticies(int stream, float* vertexBuffer, int vertexBufferSz, int offset, int stride, VertexFormat format, Vector4* trans, Vector4* scale, int to, int from, int count);
		int IndexCount();
		int InstDivisor();
		int StreamCount();
		int Option();
		size_t Size();
		std::vector<VertexFormat>* VertexFormats();
	};

}

#endif