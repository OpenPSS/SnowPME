#include <Sce/PlayStation/Core/Graphics/GraphicsExtension.hpp>

#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/PlayStation/Core/Vector4.hpp>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Graphics {

	bool VertexBuffer::GetFormatElementNormalize(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
			case VertexFormat::Float:
			case VertexFormat::Float2:
			case VertexFormat::Float3:
			case VertexFormat::Float4:
			case VertexFormat::Half:
			case VertexFormat::Half2:
			case VertexFormat::Half3:
			case VertexFormat::Half4:
			case VertexFormat::Short:
			case VertexFormat::Short2:
			case VertexFormat::Short3:
			case VertexFormat::Short4:
			case VertexFormat::UShort:
			case VertexFormat::UShort2:
			case VertexFormat::UShort3:
			case VertexFormat::UShort4:
			case VertexFormat::Byte:
			case VertexFormat::Byte2:
			case VertexFormat::Byte3:
			case VertexFormat::Byte4:
			case VertexFormat::UByte:
			case VertexFormat::UByte2:
			case VertexFormat::UByte3:
			case VertexFormat::UByte4:
			default:
				return false;

			case VertexFormat::ShortN:
			case VertexFormat::Short2N:
			case VertexFormat::Short3N:
			case VertexFormat::Short4N:
			case VertexFormat::UShortN:
			case VertexFormat::UShort2N:
			case VertexFormat::UShort3N:
			case VertexFormat::UShort4N:
			case VertexFormat::ByteN:
			case VertexFormat::Byte2N:
			case VertexFormat::Byte3N:
			case VertexFormat::Byte4N:
			case VertexFormat::UByteN:
			case VertexFormat::UByte2N:
			case VertexFormat::UByte3N:
			case VertexFormat::UByte4N:
				return true;
		}
	}

	bool VertexBuffer::GetFormatIsValid(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
			case VertexFormat::Float:
			case VertexFormat::Float2:
			case VertexFormat::Float3:
			case VertexFormat::Float4:
			case VertexFormat::Half:
			case VertexFormat::Half2:
			case VertexFormat::Half3:
			case VertexFormat::Half4:
			case VertexFormat::Short:
			case VertexFormat::Short2:
			case VertexFormat::Short3:
			case VertexFormat::Short4:
			case VertexFormat::UShort:
			case VertexFormat::UShort2:
			case VertexFormat::UShort3:
			case VertexFormat::UShort4:
			case VertexFormat::Byte:
			case VertexFormat::Byte2:
			case VertexFormat::Byte3:
			case VertexFormat::Byte4:
			case VertexFormat::UByte:
			case VertexFormat::UByte2:
			case VertexFormat::UByte3:
			case VertexFormat::UByte4:
			case VertexFormat::ShortN:
			case VertexFormat::Short2N:
			case VertexFormat::Short3N:
			case VertexFormat::Short4N:
			case VertexFormat::UShortN:
			case VertexFormat::UShort2N:
			case VertexFormat::UShort3N:
			case VertexFormat::UShort4N:
			case VertexFormat::ByteN:
			case VertexFormat::Byte2N:
			case VertexFormat::Byte3N:
			case VertexFormat::Byte4N:
			case VertexFormat::UByteN:
			case VertexFormat::UByte2N:
			case VertexFormat::UByte3N:
			case VertexFormat::UByte4N:
				return true;
			default:
				return false;
		}
	}
	ElementType VertexBuffer::GetFormatElementType(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
				return ElementType::None;

			case VertexFormat::Float:
			case VertexFormat::Float2:
			case VertexFormat::Float3:
			case VertexFormat::Float4:
				return ElementType::Float;

			case VertexFormat::Half:
			case VertexFormat::Half2:
			case VertexFormat::Half3:
			case VertexFormat::Half4:
				return ElementType::Half;

			case VertexFormat::Short:
			case VertexFormat::Short2:
			case VertexFormat::Short3:
			case VertexFormat::Short4:
				return ElementType::Short;

			case VertexFormat::UShort:
			case VertexFormat::UShort2:
			case VertexFormat::UShort3:
			case VertexFormat::UShort4:
				return ElementType::UShort;

			case VertexFormat::Byte:
			case VertexFormat::Byte2:
			case VertexFormat::Byte3:
			case VertexFormat::Byte4:
				return ElementType::Byte;

			case VertexFormat::UByte:
			case VertexFormat::UByte2:
			case VertexFormat::UByte3:
			case VertexFormat::UByte4:
				return ElementType::UByte;

			case VertexFormat::ShortN:
			case VertexFormat::Short2N:
			case VertexFormat::Short3N:
			case VertexFormat::Short4N:
				return ElementType::Short;

			case VertexFormat::UShortN:
			case VertexFormat::UShort2N:
			case VertexFormat::UShort3N:
			case VertexFormat::UShort4N:
				return ElementType::UShort;

			case VertexFormat::ByteN:
			case VertexFormat::Byte2N:
			case VertexFormat::Byte3N:
			case VertexFormat::Byte4N:
				return ElementType::Byte;

			case VertexFormat::UByteN:
			case VertexFormat::UByte2N:
			case VertexFormat::UByte3N:
			case VertexFormat::UByte4N:
				return ElementType::UByte;

			default:
				return ElementType::None;
		};
	}
	int VertexBuffer::GetFormatVectorHeight(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
			case VertexFormat::Float:
			case VertexFormat::Float2:
			case VertexFormat::Float3:
			case VertexFormat::Float4:
			case VertexFormat::Half:
			case VertexFormat::Half2:
			case VertexFormat::Half3:
			case VertexFormat::Half4:
			case VertexFormat::Short:
			case VertexFormat::Short2:
			case VertexFormat::Short3:
			case VertexFormat::Short4:
			case VertexFormat::UShort:
			case VertexFormat::UShort2:
			case VertexFormat::UShort3:
			case VertexFormat::UShort4:
			case VertexFormat::Byte:
			case VertexFormat::Byte2:
			case VertexFormat::Byte3:
			case VertexFormat::Byte4:
			case VertexFormat::UByte:
			case VertexFormat::UByte2:
			case VertexFormat::UByte3:
			case VertexFormat::UByte4:
			case VertexFormat::ShortN:
			case VertexFormat::Short2N:
			case VertexFormat::Short3N:
			case VertexFormat::Short4N:
			case VertexFormat::UShortN:
			case VertexFormat::UShort2N:
			case VertexFormat::UShort3N:
			case VertexFormat::UShort4N:
			case VertexFormat::ByteN:
			case VertexFormat::Byte2N:
			case VertexFormat::Byte3N:
			case VertexFormat::Byte4N:
			case VertexFormat::UByteN:
			case VertexFormat::UByte2N:
			case VertexFormat::UByte3N:
			case VertexFormat::UByte4N:
			default:
				return 0x1;
		}
	}
	int VertexBuffer::GetFormatVectorWidth(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
				return 0x1;
			case VertexFormat::Float:
				return 0x1;
			case VertexFormat::Float2:
				return 0x2;
			case VertexFormat::Float3:
				return 0x3;
			case VertexFormat::Float4:
				return 0x4;
			case VertexFormat::Half:
				return 0x1;
			case VertexFormat::Half2:
				return 0x2;
			case VertexFormat::Half3:
				return 0x3;
			case VertexFormat::Half4:
				return 0x4;
			case VertexFormat::Short:
				return 0x1;
			case VertexFormat::Short2:
				return 0x2;
			case VertexFormat::Short3:
				return 0x3;
			case VertexFormat::Short4:
				return 0x4;
			case VertexFormat::UShort:
				return 0x1;
			case VertexFormat::UShort2:
				return 0x2;
			case VertexFormat::UShort3:
				return 0x3;
			case VertexFormat::UShort4:
				return 0x4;
			case VertexFormat::Byte:
				return 0x1;
			case VertexFormat::Byte2:
				return 0x2;
			case VertexFormat::Byte3:
				return 0x3;
			case VertexFormat::Byte4:
				return 0x4;
			case VertexFormat::UByte:
				return 0x1;
			case VertexFormat::UByte2:
				return 0x2;
			case VertexFormat::UByte3:
				return 0x3;
			case VertexFormat::UByte4:
				return 0x4;
			case VertexFormat::ShortN:
				return 0x1;
			case VertexFormat::Short2N:
				return 0x2;
			case VertexFormat::Short3N:
				return 0x3;
			case VertexFormat::Short4N:
				return 0x4;
			case VertexFormat::UShortN:
				return 0x1;
			case VertexFormat::UShort2N:
				return 0x2;
			case VertexFormat::UShort3N:
				return 0x3;
			case VertexFormat::UShort4N:
				return 0x4;
			case VertexFormat::ByteN:
				return 0x1;
			case VertexFormat::Byte2N:
				return 0x2;
			case VertexFormat::Byte3N:
				return 0x3;
			case VertexFormat::Byte4N:
				return 0x4;
			case VertexFormat::UByteN:
				return 0x1;
			case VertexFormat::UByte2N:
				return 0x2;
			case VertexFormat::UByte3N:
				return 0x3;
			case VertexFormat::UByte4N:
				return 0x4;

			default:
				return 0x1;
		}
	}

	int VertexBuffer::GetFormatVectorSize(VertexFormat format) {
		switch (format) {
			case VertexFormat::None:
				return 0;

			case VertexFormat::Float:
				return sizeof(float);

			case VertexFormat::Float2:
				return sizeof(float) * 2;

			case VertexFormat::Float3:
				return sizeof(float) * 3;

			case VertexFormat::Float4:
				return sizeof(float) * 4;
				

			case VertexFormat::Half:
				return sizeof(half);
				
			case VertexFormat::Half2:
				return sizeof(half) * 2;
				
			case VertexFormat::Half3:
				return sizeof(half) * 3;
				
			case VertexFormat::Half4:
				return sizeof(half) * 4;
				

			case VertexFormat::Short:
				return sizeof(short);
				
			case VertexFormat::Short2:
				return sizeof(short) * 2;
				
			case VertexFormat::Short3:
				return sizeof(short) * 3;
				
			case VertexFormat::Short4:
				return sizeof(short) * 4;
				

			case VertexFormat::UShort:
				return sizeof(unsigned short);
				
			case VertexFormat::UShort2:
				return sizeof(unsigned short) * 2;
				
			case VertexFormat::UShort3:
				return sizeof(unsigned short) * 3;
				
			case VertexFormat::UShort4:
				return sizeof(unsigned short) * 4;
				

			case VertexFormat::Byte:
				return sizeof(byte);
				
			case VertexFormat::Byte2:
				return sizeof(byte) * 2;
				
			case VertexFormat::Byte3:
				return sizeof(byte) * 3;
				
			case VertexFormat::Byte4:
				return sizeof(byte) * 4;
				

			case VertexFormat::UByte:
				return sizeof(ubyte);
				
			case VertexFormat::UByte2:
				return sizeof(ubyte) * 2;
				
			case VertexFormat::UByte3:
				return sizeof(ubyte) * 3;
				
			case VertexFormat::UByte4:
				return sizeof(ubyte) * 4;
				


			case VertexFormat::ShortN:
				return sizeof(short);
				
			case VertexFormat::Short2N:
				return sizeof(short) * 2;
				
			case VertexFormat::Short3N:
				return sizeof(short) * 3;
				
			case VertexFormat::Short4N:
				return sizeof(short) * 4;
				

			case VertexFormat::UShortN:
				return sizeof(unsigned short);
				
			case VertexFormat::UShort2N:
				return sizeof(unsigned short) * 2;
				
			case VertexFormat::UShort3N:
				return sizeof(unsigned short) * 3;
				
			case VertexFormat::UShort4N:
				return sizeof(unsigned short) * 4;
				

			case VertexFormat::ByteN:
				return sizeof(byte);
				
			case VertexFormat::Byte2N:
				return sizeof(byte) * 2;
				
			case VertexFormat::Byte3N:
				return sizeof(byte) * 3;
				
			case VertexFormat::Byte4N:
				return sizeof(byte) * 4;
				

			case VertexFormat::UByteN:
				return sizeof(ubyte);
				
			case VertexFormat::UByte2N:
				return sizeof(ubyte) * 2;
				
			case VertexFormat::UByte3N:
				return sizeof(ubyte) * 3;
				
			case VertexFormat::UByte4N:
				return sizeof(ubyte) * 4;


			default:
				return 0;
		}
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

	int VertexBuffer::StreamCount() {
		return (int)VertexFormats()->size();
	}

	std::vector<VertexFormat>* VertexBuffer::VertexFormats() {
		return this->vertexFormats;
	}

	int VertexBuffer::doTranslationAndScale(VertexFormat inputFormat, VertexFormat* outputFormat, Vector4** trans, Vector4** scale) {
		bool result = false;


		// Check provided formats are correct ...
		VertexFormat outpFormat = *outputFormat;
		if (outpFormat != VertexFormat::None) {
			if (inputFormat == outpFormat) {
				result = false;
			}
			else {
				bool isValid = VertexBuffer::GetFormatIsValid(outpFormat);
				ElementType type = VertexBuffer::GetFormatElementType(outpFormat);
				int formatVectorWidth = VertexBuffer::GetFormatVectorWidth(outpFormat);
				int formatVectorHeight = VertexBuffer::GetFormatVectorHeight(outpFormat);

				if ((!isValid || type != ElementType::Float) ||
					(formatVectorWidth != VertexBuffer::GetFormatVectorWidth(inputFormat)) ||
					(formatVectorHeight != VertexBuffer::GetFormatVectorHeight(inputFormat))
					) {
					*outputFormat = VertexFormat::None;
					return PSM_ERROR_NO_ERROR;
				}

				result = true;
			}

		}
		else
		{
			*outputFormat = inputFormat;
			result = false;
		}


		// Do we need **Trans Rights** ???
		Vector4* transRights = *trans;
		if (transRights->X != 0.0 || transRights->Y != 0.0 || transRights->Z != 0.0 || transRights->W != 0.0) {
			result = true;

			Vector4 transLefts;
			transLefts.X = -transRights->X;
			transLefts.Y = -transRights->Y;
			transLefts.Z = -transRights->Z;
			transLefts.W = -transRights->W;

			memcpy(trans, &transLefts, sizeof(Vector4));
		}
		

		// Do we need Scale ???

		Vector4* scaleRights = *scale;
		if (scaleRights->X != 0.0 || scaleRights->Y != 0.0) {
			if (scaleRights->X == 0.0) {
				result = true;

			}

		}

	}

	int VertexBuffer::SetVerticies(int stream, float* vertexBuffer, size_t vertexBufferSz, int offset, int stride, VertexFormat format, Vector4* trans, Vector4* scale, int to, int from, int count) {
		if (!vertexBuffer)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (stream < 0 || stream >= this->StreamCount())
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		if (!GetFormatIsValid(format))
			return PSM_ERROR_COMMON_ARGUMENT;

		VertexFormat streamCurrentFormat = VertexFormats()->at(stream);
		doTranslationAndScale(streamCurrentFormat, &format, &trans, &scale);

		if (format != VertexFormat::None) {
			ExceptionInfo::AddMessage("Incompatible format with vertex stream");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		return PSM_ERROR_NO_ERROR;
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