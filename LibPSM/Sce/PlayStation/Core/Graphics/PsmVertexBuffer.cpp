#include "PsmVertexBuffer.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* formats, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmVertexBuffer::Delete(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmVertexBuffer::AddRef(int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmVertexBuffer::SetVertices(int handle, int* vertices, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmVertexBuffer::SetVertices2(int handle, int stream, int* vertices, VertexFormat format, Vector4* trans, Vector4* scale, int offset, int stride, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmVertexBuffer::SetIndices(int handle, uint16_t* indices, int to, int from, int count){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
