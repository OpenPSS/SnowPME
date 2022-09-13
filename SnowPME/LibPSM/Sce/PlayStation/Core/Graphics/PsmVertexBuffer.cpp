#include "PsmVertexBuffer.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* formats, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::Create(int, int, int, int, Sce::PlayStation::Core::Graphics::VertexFormat*, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmVertexBuffer::Delete(int handle) {
		cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << endl;
		return 0;
	}
	int PsmVertexBuffer::AddRef(int handle) {
		cout << "Sce::PlayStation::Core::Graphics::AddRef(int) Unimplemented." << endl;
		return 0;
	}
	int PsmVertexBuffer::SetVertices(int handle, int* vertices, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetVertices(int, System::Array, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmVertexBuffer::SetVertices2(int handle, int stream, int* vertices, VertexFormat format, Vector4* trans, Vector4* scale, int offset, int stride, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetVertices2(int, int, System::Array, Sce::PlayStation::Core::Graphics::VertexFormat, Sce::PlayStation::Core::Vector4 *, Sce::PlayStation::Core::Vector4 *, int, int, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmVertexBuffer::SetIndices(int handle, uint16_t* indices, int to, int from, int count){
		cout << "Sce::PlayStation::Core::Graphics::SetIndices(int, uint16_t*, int, int, int) Unimplemented." << endl;
		return 0;
	}
}
