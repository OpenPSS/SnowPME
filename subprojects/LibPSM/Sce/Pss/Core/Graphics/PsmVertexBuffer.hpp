#ifndef LIB_PSS_PSMVERTEXBUFFER_H
#define LIB_PSS_PSMVERTEXBUFFER_H 1
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <mono/mono.h>

#include "VertexFormat.hpp"
#include "../Vector4.hpp"


namespace Sce::Pss::Core::Graphics {
	class PsmVertexBuffer {
	public:
		static int Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray *formats, int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int SetVertices(int handle, int *vertices, int to, int from, int count);
		static int SetVertices2(int handle, int stream, MonoArray* vertices, VertexFormat format, Vector4 *trans, Vector4 *scale, int offset, int stride, int to, int from, int count);
		static int SetIndices(int handle, uint16_t* indices, int to, int from, int count);
	};
}
#endif
