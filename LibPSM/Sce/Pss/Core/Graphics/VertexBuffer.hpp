#ifndef LIB_PSM_VERTEXBUFFER_H
#define LIB_PSM_VERTEXBUFFER_H 1
#include <cstdint>
#include <vector>
#include <Sce/PlayStation/Core/Graphics/VertexFormat.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

using namespace Sce::PlayStation::Core::Graphics;

namespace Sce::Pss::Core::Graphics {

	typedef uint16_t half;
	typedef int8_t byte;
	typedef uint8_t ubyte;

	class VertexBuffer : public Errorable {
	private:
		int vertexCount = 0;
		int indexCount = 0;
		int instDivisor = 0;
		int option = 0;
		uint32_t buffer = 0;
		size_t size = 0;
		std::vector<VertexFormat>* vertexFormats = NULL;
	public:
		VertexBuffer(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* vertexFormats, int vertexFormatsLen);
		~VertexBuffer();
		int GetFormatVectorSize(VertexFormat format);
		int VertexCount();
		int IndexCount();
		int InstDivisor();
		int Option();
		uint32_t Buffer();
		size_t Size();
		std::vector<VertexFormat>* VertexFormats();
	};

}

#endif