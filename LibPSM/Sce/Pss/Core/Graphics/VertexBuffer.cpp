#include <Sce/PlayStation/Core/Graphics/GraphicsExtension.hpp>

#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Graphics {

	int VertexBuffer::GetFormatVectorSize(VertexFormat format) {
		int sz = 0;
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
			ExceptionInfo::AddMessage("Unsupported format on this device");
			this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
			return 0;
		}

		return sz;
	}
	VertexBuffer::~VertexBuffer() {
		if (this->vertexFormats != NULL) {
			delete this->vertexFormats;
		}
	}
	int VertexBuffer::VertexCount() {
		return this->vertexCount;
	}
	int VertexBuffer::IndexCount() {
		return this->indexCount;
	}
	int VertexBuffer::InstDivisor() {
		return this->instDivisor;
	}
	int VertexBuffer::Option() {
		return this->option;
	}
	uint32_t VertexBuffer::Buffer() {
		return this->buffer;
	}
	size_t VertexBuffer::Size() {
		return this->size;
	}
	std::vector<VertexFormat>* VertexBuffer::VertexFormats() {
		return this->vertexFormats;
	}

	VertexBuffer::VertexBuffer(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* vertexFormats, int vertexFormatsLen) {
		if (Thread::IsMainThread()) {
			if (GraphicsContext::GetGraphicsContext() == NULL) {
				this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
				return;
			}
			this->vertexFormats = new std::vector<VertexFormat>();

			// Get graphics context
			GraphicsContext* graphicsContext = GraphicsContext::GetGraphicsContext();

			// Store state passed to parameters
			this->vertexCount = vertexCount;
			this->instDivisor = instDivisor;
			this->option = option;
			this->indexCount = indexCount;


			// Check arguments are valid

			// is vertexFormats null, or less than 0 formats?
			if (vertexFormats == NULL && vertexFormatsLen > 0) {
				this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
				return;
			}

			// Is there more than 0xFFFF vertexes, or indexes? 
			// are there more than 0x100 unique formats?
			// is the instDivisor > 1?
			// if any of those are true, error
			if (vertexCount > 0xFFFF || indexCount > 0xFFFF || vertexFormatsLen > 0x100 || instDivisor > 1) {
				this->SetError(PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE);
				return;
			}

			// is option set?
			if (option != NULL) {
				this->SetError(PSM_ERROR_COMMON_ARGUMENT);
				return;
			}

			int extensions = graphicsContext->CapsState()->Extension;
			if (instDivisor && (extensions & GraphicsExtension::InstancedArrays) == 0) {
				ExceptionInfo::AddMessage("Unsupported extension on this device");
				this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
				return;
			}

			while (glGetError()) {};

			uint32_t glBuf = 0;
			glGenBuffers(1, &glBuf);
			this->buffer = glBuf;

			size_t sz = 0;

			// Determine required buffer size
			for (int i = 0; i < vertexFormatsLen; i++) {
				VertexFormat format = vertexFormats[i];

				int versionFormatSz = this->GetFormatVectorSize(format);

				// handle errors
				if (this->GetError() != PSM_ERROR_NO_ERROR)
					return;

				if (versionFormatSz < 0)
					sz += versionFormatSz;

				this->VertexFormats()->push_back(format);
			}

			sz *= this->VertexCount();

			this->size = sz;

			// Allocate array buffer in opengl.

			graphicsContext->BindArrayBuffer(this->Buffer());
			glBufferData(GL_ARRAY_BUFFER, sz, 0, GL_STATIC_DRAW);
			graphicsContext->BindArrayBuffer(0);
			if (glGetError() == GL_OUT_OF_MEMORY) {
				this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
				return;
			}


		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}

}