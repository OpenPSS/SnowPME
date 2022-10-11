#include "PsmGraphicsContext.hpp"
#include "PsmVertexBuffer.hpp"
#include "../Error.hpp"

#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;


namespace Sce::PlayStation::Core::Graphics {
	size_t PsmVertexBuffer::determineVertexFormatSize(VertexFormat format) {
		size_t sz = 0;
		switch (format) {
		case VertexFormat::Float:
			sz += sizeof(float);
			break;

		case VertexFormat::Float2:
			sz += sizeof(float) * 2;
			break;

		case VertexFormat::Float3:
			sz += sizeof(float) * 3;
			break;

		case VertexFormat::Float4:
			sz += sizeof(float) * 4;
			break;

		case VertexFormat::Half:
			sz += sizeof(half);
			break;
		case VertexFormat::Half2:
			sz += sizeof(half) * 2;
			break;
		case VertexFormat::Half3:
			sz += sizeof(half) * 3;
			break;
		case VertexFormat::Half4:
			sz += sizeof(half) * 4;
			break;

		case VertexFormat::Short:
			sz += sizeof(short);
			break;
		case VertexFormat::Short2:
			sz += sizeof(short) * 2;
			break;
		case VertexFormat::Short3:
			sz += sizeof(short) * 3;
			break;
		case VertexFormat::Short4:
			sz += sizeof(short) * 4;
			break;

		case VertexFormat::UShort:
			sz += sizeof(unsigned short);
			break;
		case VertexFormat::UShort2:
			sz += sizeof(unsigned short) * 2;
			break;
		case VertexFormat::UShort3:
			sz += sizeof(unsigned short) * 3;
			break;
		case VertexFormat::UShort4:
			sz += sizeof(unsigned short) * 4;
			break;

		case VertexFormat::Byte:
			sz += sizeof(byte);
			break;
		case VertexFormat::Byte2:
			sz += sizeof(byte) * 2;
			break;
		case VertexFormat::Byte3:
			sz += sizeof(byte) * 3;
			break;
		case VertexFormat::Byte4:
			sz += sizeof(byte) * 4;
			break;

		case VertexFormat::UByte:
			sz += sizeof(ubyte);
			break;
		case VertexFormat::UByte2:
			sz += sizeof(ubyte) * 2;
			break;
		case VertexFormat::UByte3:
			sz += sizeof(ubyte) * 3;
			break;
		case VertexFormat::UByte4:
			sz += sizeof(ubyte) * 4;
			break;


		case VertexFormat::ShortN:
			sz += sizeof(short);
			break;
		case VertexFormat::Short2N:
			sz += sizeof(short) * 2;
			break;
		case VertexFormat::Short3N:
			sz += sizeof(short) * 3;
			break;
		case VertexFormat::Short4N:
			sz += sizeof(short) * 4;
			break;

		case VertexFormat::UShortN:
			sz += sizeof(unsigned short);
			break;
		case VertexFormat::UShort2N:
			sz += sizeof(unsigned short) * 2;
			break;
		case VertexFormat::UShort3N:
			sz += sizeof(unsigned short) * 3;
			break;
		case VertexFormat::UShort4N:
			sz += sizeof(unsigned short) * 4;
			break;

		case VertexFormat::ByteN:
			sz += sizeof(byte);
			break;
		case VertexFormat::Byte2N:
			sz += sizeof(byte) * 2;
			break;
		case VertexFormat::Byte3N:
			sz += sizeof(byte) * 3;
			break;
		case VertexFormat::Byte4N:
			sz += sizeof(byte) * 4;
			break;

		case VertexFormat::UByteN:
			sz += sizeof(ubyte);
		case VertexFormat::UByte2N:
			sz += sizeof(ubyte) * 2;
		case VertexFormat::UByte3N:
			sz += sizeof(ubyte) * 3;
		case VertexFormat::UByte4N:
			sz += sizeof(ubyte) * 4;

		case VertexFormat::None:
		default:
			Logger::Error("VertexFormat was None or Unknown.");
			break;
		}

		return sz;
	}
	int PsmVertexBuffer::Create(int vertexCount, int indexCount, int instDivisor, int option, MonoArray* formats, int* result) {
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
			GraphicsContext* graphicsContext = PsmGraphicsContext::GetContext();

			VertexBuffer* vertexBuffer = new VertexBuffer();

			vertexBuffer->VertexCount = vertexCount;
			vertexBuffer->InstDivisor = instDivisor;
			vertexBuffer->Option = option;
			vertexBuffer->IndexCount = indexCount;

			VertexFormat* vertexFormats = (VertexFormat*)mono_array_addr_with_size(formats, 1, 0);
			int vertexFormatsLen = mono_array_length(formats);

			if (vertexFormats == NULL && vertexFormatsLen > 0)
				return PSM_ERROR_COMMON_ARGUMENT_NULL;

			if (vertexCount > 0xFFFF || indexCount > 0xFFFF || vertexFormatsLen > 0x100 || instDivisor > 1)
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

			if (option)
				return PSM_ERROR_COMMON_ARGUMENT;

			int extensions = graphicsContext->CapsState->Extension;
			if (instDivisor && (extensions & GraphicsExtension::InstancedArrays) == 0) {
				Logger::Error("Unsupported extension on this device");
				return PSM_ERROR_COMMON_NOT_SUPPORTED;
			}

			ClearOpenGLErrors();

			glGenBuffers(1, &vertexBuffer->Buffer);
			
			size_t sz = 0;

			for (int i = 0; i < vertexFormatsLen; i++) {
				VertexFormat format = vertexFormats[i];
				sz += determineVertexFormatSize(format);
				vertexBuffer->VertexFormats.push_back(format);
			}

			sz *= vertexCount; 
			vertexBuffer->Size = sz;

			PsmGraphicsContext::BindArrayBuffer(vertexBuffer->Buffer);
			glBufferData(GL_ARRAY_BUFFER, sz, 0, GL_STATIC_DRAW);
			PsmGraphicsContext::BindArrayBuffer(0);
			if (glGetError() == GL_OUT_OF_MEMORY)
				return PSM_ERROR_COMMON_OUT_OF_MEMORY;

			*result = (uint32_t)vertexBuffer;


			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

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
