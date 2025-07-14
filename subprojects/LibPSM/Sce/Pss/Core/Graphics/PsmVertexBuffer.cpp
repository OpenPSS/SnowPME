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
using namespace Sce::Pss::Core::Mono;

namespace Sce::Pss::Core::Graphics {


	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray* formats, int* result) {
		LOG_FUNCTION();

		VertexFormat* vertexFormats = reinterpret_cast<VertexFormat*>(mono_array_addr_with_size(formats, 1, 0));
		int vertexFormatsLen = mono_array_length(formats);
		VertexBuffer* vtxBuf = VertexBuffer::Create(vertexCount, indexCount, vertexFormats, vertexFormatsLen, instDivisor, option);
		RETURN_ERRORABLE_GRAPHICSOBJECT(vtxBuf, VertexBuffer);

		*result = vtxBuf->Handle();

		return PSM_ERROR_NO_ERROR;
	}
	int PsmVertexBuffer::Delete(int handle) {
		LOG_FUNCTION();

		if (Handles<VertexBuffer>::IsValid(handle)) {

			if (!Thread::IsMainThread()) {
				VertexBuffer::Release(handle);

				return PSM_ERROR_NO_ERROR;
			}
			else {
				UNIMPLEMENTED_MSG("Trying to delete VertexBuffer cross-thread (TODO: Notify main thread?)");
			}
		}
		return PSM_ERROR_NO_ERROR;
	}
	int PsmVertexBuffer::AddRef(int handle) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			return VertexBuffer::AddRef(handle) != false ? PSM_ERROR_NO_ERROR : PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}
		ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
		return PSM_ERROR_COMMON_INVALID_OPERATION;
	}
	int PsmVertexBuffer::SetVertices(int handle, MonoArray* vertices, int to, int from, int count) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObject() == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;
			VertexBuffer* buffer = Handles<VertexBuffer>::GetRaw(handle);
			if (buffer == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

			void* verticiesBuffer = nullptr;

			if (vertices != nullptr) {
				MonoType* type = MonoUtil::MonoArrayElementsType(vertices);

				if (!MonoUtil::MonoTypeIsValueType(type)) {
					ExceptionInfo::SetMessage("Vertex data need to be ValueType\n");
					return PSM_ERROR_COMMON_INVALID_OPERATION;
				}

				verticiesBuffer = mono_array_addr_with_size(vertices, 1, 0);
			}
			size_t arrayLen = MonoUtil::MonoArrayBytesLength(vertices);

			if (count > 0 || !vertices || arrayLen == (buffer->VertexCount * buffer->VertexSize)) {
				return buffer->SetVerticies(reinterpret_cast<float*>(verticiesBuffer), arrayLen, to, from);
			}
			ExceptionInfo::AddMessage("Vertex array has wrong size\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmVertexBuffer::SetVertices2(int handle, int stream, MonoArray* vertices, VertexFormat format, Vector4* trans, Vector4* scale, int offset, int stride, int to, int from, int count) {
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			if (GraphicsContext::UniqueObject() == nullptr) return PSM_ERROR_GRAPHICS_SYSTEM;
			VertexBuffer* buffer = Handles<VertexBuffer>::GetRaw(handle);
			if (buffer == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

			MonoType* type = MonoUtil::MonoArrayElementsType(vertices);
			
			if (!MonoUtil::MonoTypeIsValueType(type)) {
				ExceptionInfo::AddMessage("Vertex data need to be ValueType\n");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}

			void* verticesBuffer = reinterpret_cast<void*>(mono_array_addr_with_size(vertices, 1, 0));
			size_t arrayLen = MonoUtil::MonoArrayBytesLength(vertices);

			// if count < 0, set the count to the vertex count
			if (count < 0) {
				count = buffer->VertexCount;
			}

			// Check the stream number is valid
			if (stream < 0 || stream >= static_cast<int>(buffer->VertexFormats.size())) {
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}

			// Check the size is what is expected.
			int formatSize = buffer->GetFormatVectorSize(buffer->VertexFormats[stream]);
			if (arrayLen != buffer->VertexCount * formatSize) {
				ExceptionInfo::AddMessage("Vertex array has wrong size\n");
				return PSM_ERROR_COMMON_INVALID_OPERATION;
			}
			
			return buffer->SetVerticies(stream, reinterpret_cast<float*>(verticesBuffer), arrayLen, offset, stride, format, trans, scale, to, from, count);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		
	}
	int PsmVertexBuffer::SetIndices(int handle, MonoArray* indices, int to, int from, int count) {
		LOG_FUNCTION();
		UNIMPLEMENTED();
	}
}
