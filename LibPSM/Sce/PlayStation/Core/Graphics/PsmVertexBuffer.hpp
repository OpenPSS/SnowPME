#ifndef LIB_PSM_PSMVERTEXBUFFER_H
#define LIB_PSM_PSMVERTEXBUFFER_H 1
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <mono/mono.h>

#include "VertexFormat.hpp"
#include "../Vector4.hpp"
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Graphics {
	
	typedef uint16_t half;
	typedef int8_t byte;
	typedef uint8_t ubyte;

	typedef struct VertexBuffer {
		int VertexCount;
		int IndexCount;
		int InstDivisor;
		int Option;
		uint32_t Buffer;
		size_t Size;
		std::vector<VertexFormat> VertexFormats;
	} VertexBuffer;

	class PsmVertexBuffer {
	private:
		static size_t determineVertexFormatSize(VertexFormat format);
	public:
		static int Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray *formats, int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int SetVertices(int handle, int *vertices, int to, int from, int count);
		static int SetVertices2(int handle, int stream, int *vertices, VertexFormat format, Vector4 *trans, Vector4 *scale, int offset, int stride, int to, int from, int count);
		static int SetIndices(int handle, uint16_t* indices, int to, int from, int count);
	};
}
#endif
