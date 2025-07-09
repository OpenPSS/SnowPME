#include <Sce/Pss/Core/Graphics/PsmVertexBuffer.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>

#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Graphics {


	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray* formats, int* result) {
		LOG_FUNCTION();

		VertexFormat* vertexFormats = (VertexFormat*)mono_array_addr_with_size(formats, 1, 0);
		int vertexFormatsLen = mono_array_length(formats);

		std::shared_ptr<VertexBuffer> vtxBuf = VertexBuffer::Create(vertexCount, indexCount, instDivisor, option, vertexFormats, vertexFormatsLen);
		RETURN_ERRORABLE_PSMOBJECT(vtxBuf, VertexBuffer);

		*result = vtxBuf->Handle();

		return PSM_ERROR_NO_ERROR;
	}
	int PsmVertexBuffer::Delete(int handle) {
		UNIMPLEMENTED();
	}
	int PsmVertexBuffer::AddRef(int handle) {
		UNIMPLEMENTED();
	}
	int PsmVertexBuffer::SetVertices(int handle, int* vertices, int to, int from, int count) {
		UNIMPLEMENTED();
	}
	int PsmVertexBuffer::SetVertices2(int handle, int stream, MonoArray* vertices, VertexFormat format, Vector4* trans, Vector4* scale, int offset, int stride, int to, int from, int count) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObject() == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;
			std::shared_ptr<VertexBuffer> buffer = Handles<VertexBuffer>::Get(handle);
			if (buffer == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

			MonoType* type = Sce::Pss::Core::Mono::MonoUtil::MonoArrayElementsType(vertices);
			
			if (!Sce::Pss::Core::Mono::MonoUtil::MonoTypeIsValueType(type)) {
				Logger::Error("Vertex data need to be ValueType");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}

			void* verticesBuffer = reinterpret_cast<void*>(mono_array_addr_with_size(vertices, 1, 0));
			size_t arrayLen = Sce::Pss::Core::Mono::MonoUtil::MonoArrayBytesLength(vertices);

			// if count < 0, set the count to the vertex count
			if (count < 0) {
				count = buffer->VertexCount;
			}

			// Check the stream number is valid
			if (stream < 0 || stream >= static_cast<int>(buffer->VertexFormats.size())) {
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}

			// Check the size is what is expected.
			int formatSize = buffer->GetFormatVectorSize(buffer->VertexFormats.at(stream));
			if (arrayLen != buffer->VertexCount * formatSize) {
				Logger::Error("Vertex array has wrong size");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}
			
			return buffer->SetVerticies(stream, (float*)verticesBuffer, arrayLen, offset, stride, format, trans, scale, to, from, count);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		
	}
	int PsmVertexBuffer::SetIndices(int handle, uint16_t* indices, int to, int from, int count){
		UNIMPLEMENTED();
	}
}
