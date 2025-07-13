#ifndef LIB_PSS_VERTEXBUFFER_H
#define LIB_PSS_VERTEXBUFFER_H 1
#include <cstdint>
#include <vector>
#include <Sce/Pss/Core/Vector4.hpp>
#include <Sce/Pss/Core/Graphics/ElementType.hpp>
#include <Sce/Pss/Core/Graphics/VertexFormat.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>

namespace Sce::Pss::Core::Graphics {

	typedef uint16_t half;
	typedef int8_t byte;
	typedef uint8_t ubyte;

	class VertexBuffer : public GraphicsObject<VertexBuffer> {
	private:
		bool translationScaleNormalize(VertexFormat inputFormat, VertexFormat* outputFormat, Vector4** trans, Vector4** scale);
	public:
		VertexBuffer(int vertexCount, int indexCount, int numStreams, int option, VertexFormat* vertexFormats, int vertexFormatsLen);
		~VertexBuffer() = default;

		static bool GetFormatIsValid(VertexFormat format);
		static ElementType GetFormatElementType(VertexFormat format);
		static int GetFormatVectorHeight(VertexFormat format);
		static int GetFormatVectorWidth(VertexFormat format);
		static int GetFormatVectorSize(VertexFormat format);
		static bool GetFormatElementNormalize(VertexFormat format);
		static int GetFormatElementSize(VertexFormat format);
		int SetVerticies(float* vertexBuffer, int vertexBufferSz, int to, int from);
		int SetVerticies(int stream, float* vertexBuffer, int vertexBufferSz, int offset, int stride, VertexFormat format, Vector4* trans, Vector4* scale, int to, int from, int count);
		
		std::vector<VertexFormat> VertexFormats;
		int VertexCount = 0;
		int IndexCount = 0;
		int NumStreams = 0;
		int Option = 0;
		size_t Size = 0;
		bool unk21 = true;
	};

}

#endif