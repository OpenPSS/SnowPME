#include <Sce/PlayStation/Core/Graphics/PsmVertexBuffer.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;
using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Threading;

namespace Sce::PlayStation::Core::Graphics {
	
	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray* formats, int* result) {
		Logger::Debug(__FUNCTION__);

		VertexFormat* vertexFormats = (VertexFormat*)mono_array_addr_with_size(formats, 1, 0);
		int vertexFormatsLen = mono_array_length(formats);

		VertexBuffer* vertxBuffer = new VertexBuffer(vertexCount, indexCount, instDivisor, option, vertexFormats, vertexFormatsLen);
		ReturnErrorable(vertxBuffer);

		*result = Handles::CreateHandle((uintptr_t)vertxBuffer);

		return PSM_ERROR_NO_ERROR;
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
	int PsmVertexBuffer::SetVertices2(int handle, int stream, MonoArray* vertices, VertexFormat format, Vector4* trans, Vector4* scale, int offset, int stride, int to, int from, int count) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetGraphicsContext() == NULL) return PSM_ERROR_GRAPHICS_SYSTEM;
			VertexBuffer* buffer = (VertexBuffer*)Handles::GetHandle(handle);
			if (buffer == NULL) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

			MonoType* type = MonoUtil::MonoArrayElementsType(vertices);
			
			if (!MonoUtil::MonoTypeIsValueType(type)) {
				Logger::Error("Vertex data need to be ValueType");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}

			void* verticesBuffer = (void*)mono_array_addr_with_size(vertices, 1, 0);
			size_t arrayLen = MonoUtil::MonoArrayLength(vertices);

			// Check the stream number is valid
			if (stream < 0 || stream >= (int)buffer->VertexFormats()->size()) {
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}

			// Check the size is what is expected.
			int formatSize = buffer->GetFormatVectorSize((*buffer->VertexFormats())[stream]);
			if (arrayLen != buffer->VertexCount() * formatSize) {
				Logger::Error("Vertex array has wrong size");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}

			return buffer->SetVerticies(stream, (float*)verticesBuffer, arrayLen, offset, stride, format, trans, scale, to, from, count);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		
	}
	int PsmVertexBuffer::SetIndices(int handle, uint16_t* indices, int to, int from, int count){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
