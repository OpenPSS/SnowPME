#ifndef LIB_PSM_PSMVERTEXBUFFER_H
#define LIB_PSM_PSMVERTEXBUFFER_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "VertexFormat.hpp"
#include "../Vector4.hpp"
using namespace Sce::PlayStation::Core;
using namespace std;

namespace Sce::PlayStation::Core::Graphics {
	class PsmVertexBuffer {
	public:
		static int Create(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat *formats, int *result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int SetVertices(int handle, int *vertices, int to, int from, int count);
		static int SetVertices2(int handle, int stream, int *vertices, VertexFormat format, Vector4 *trans, Vector4 *scale, int offset, int stride, int to, int from, int count);
		static int SetIndices(int handle, uint16_t* indices, int to, int from, int count);
	};
}
#endif
