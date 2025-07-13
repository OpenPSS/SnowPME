#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>

#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsContext.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Vector4.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>
#include <string.h>

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;
using namespace Shared::Debug;

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
	int VertexBuffer::GetFormatElementSize(VertexFormat format) {
		switch (format) {
			default:
			case VertexFormat::None:
				return 0x0;
			case VertexFormat::Float:
			case VertexFormat::Float2:
			case VertexFormat::Float3:
			case VertexFormat::Float4:
				return sizeof(float);
			case VertexFormat::Half:
			case VertexFormat::Half2:
			case VertexFormat::Half3:
			case VertexFormat::Half4:
				return sizeof(half);
			case VertexFormat::Short:
			case VertexFormat::Short2:
			case VertexFormat::Short3:
			case VertexFormat::Short4:
				return sizeof(short);
			case VertexFormat::UShort:
			case VertexFormat::UShort2:
			case VertexFormat::UShort3:
			case VertexFormat::UShort4:
				return sizeof(unsigned short);
			case VertexFormat::Byte:
			case VertexFormat::Byte2:
			case VertexFormat::Byte3:
			case VertexFormat::Byte4:
				return sizeof(byte);
			case VertexFormat::UByte:
			case VertexFormat::UByte2:
			case VertexFormat::UByte3:
			case VertexFormat::UByte4:
				return sizeof(ubyte);
			case VertexFormat::ShortN:
			case VertexFormat::Short2N:
			case VertexFormat::Short3N:
			case VertexFormat::Short4N:
				return sizeof(short);
			case VertexFormat::UShortN:
			case VertexFormat::UShort2N:
			case VertexFormat::UShort3N:
			case VertexFormat::UShort4N:
				return sizeof(unsigned short);
			case VertexFormat::ByteN:
			case VertexFormat::Byte2N:
			case VertexFormat::Byte3N:
			case VertexFormat::Byte4N:
				return sizeof(byte);
			case VertexFormat::UByteN:
			case VertexFormat::UByte2N:
			case VertexFormat::UByte3N:
			case VertexFormat::UByte4N:
				return sizeof(ubyte);
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

	bool VertexBuffer::translationScaleNormalize(VertexFormat inputFormat, VertexFormat* outputFormat, Vector4** trans, Vector4** scale) {
		bool changed = false;

		// Check provided formats are correct ...
		VertexFormat outpFormat = *outputFormat;
		if (outpFormat != VertexFormat::None) {
			if (inputFormat == outpFormat) {
				changed = false;
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
					return false;
				}

				changed = true;
			}

		}
		else
		{
			*outputFormat = inputFormat;
			changed = false;
		}

		// Do we need to invert the transform
		Vector4* transRef = *trans;
		if (transRef->X != 0.0f || transRef->Y != 0.0f || transRef->Z != 0.0f || transRef->W != 0.0f) {
			changed = true;

			Vector4 transInverted;
			transInverted.X = -transRef->X;
			transInverted.Y = -transRef->Y;
			transInverted.Z = -transRef->Z;
			transInverted.W = -transRef->W;

			memcpy(*trans, &transInverted, sizeof(Vector4));
		}
		

		// Do we need Scale ???

		Vector4* scaleRef = *scale;
		if (scaleRef->X != 1.0f || scaleRef->Y != 1.0f || scaleRef->Z != 1.0f || scaleRef->W != 1.0f) {
			changed = true;
			Vector4 newScale;

			// If its 0 set it to 0 (avoid devide by 0 errors) 
			// otherwise, scale by the factor

			if (scaleRef->X == 0.0f)
				newScale.X = 0.0f;
			else
				newScale.X = 1.0f / scaleRef->X;

			if (scaleRef->Y == 0.0f)
				newScale.Y = 0.0f;
			else
				newScale.Y = 1.0f / scaleRef->Y;

			if (scaleRef->Z == 0.0f)
				newScale.Z = 0.0f;
			else
				newScale.Z = 1.0f / scaleRef->Z;

			if (scaleRef->W == 0.0f)
				newScale.W = 0.0f;
			else
				newScale.W = 1.0f / scaleRef->W;

			memcpy(*scale, &newScale, sizeof(Vector4));
		}
		else if (!changed) {
			return changed;
		}

		// Do we need to normalize this ?

		if (!GetFormatElementNormalize(inputFormat))
			return changed;

		ElementType elemType = GetFormatElementType(inputFormat);

		Vector4 newScale;
		Vector4 newTrans;

		if (elemType == ElementType::UShort) {
			// Multiply by the types max value, as a float

			newScale.X = scaleRef->X * 65535.0f;
			newScale.Y = scaleRef->Y * 65535.0f;
			newScale.Z = scaleRef->Z * 65535.0f;
			newScale.W = scaleRef->W * 65535.0f;

			memcpy(*scale, &newScale, sizeof(Vector4));
			return changed;
		}
		else if (elemType == ElementType::Short) {
			// i took this '-0.000015259f' constant directly from PSM Runtime,
			// i have no idea what this constant is actually for, or why it specifically was chosen.

			newTrans.X = transRef->X + (-0.000015259f * scaleRef->X);
			newTrans.Y = transRef->Y + (-0.000015259f * scaleRef->Y);
			newTrans.Z = transRef->Z + (-0.000015259f * scaleRef->Z);
			newTrans.W = transRef->W + (-0.000015259f * scaleRef->W);
			
			// Multiply by the types max value, as a float

			newScale.X = scaleRef->X * 32768.0f;
			newScale.Y = scaleRef->Y * 32768.0f;
			newScale.Z = scaleRef->Z * 32768.0f;
			newScale.Z = scaleRef->W * 32768.0f;

			memcpy(*trans, &newTrans, sizeof(Vector4));
			memcpy(*scale, &newScale, sizeof(Vector4));
			return changed;
		}
		else if (elemType == ElementType::Byte) {
			// i took this '-0.0039216f' constant directly from PSM Runtime,
			// i have no idea what this constant is actually for, or why it specifically was chosen.

			newTrans.X = transRef->X + (-0.0039216f * scaleRef->X);
			newTrans.Y = transRef->Y + (-0.0039216f * scaleRef->Y);
			newTrans.Z = transRef->Z + (-0.0039216f * scaleRef->Z);
			newTrans.W = transRef->W + (-0.0039216f * scaleRef->W);

			// Multiply by the types max value, as a float

			newScale.X = scaleRef->X * 127.5f;
			newScale.Y = scaleRef->Y * 127.5f;
			newScale.Z = scaleRef->Z * 127.5f;
			newScale.Z = scaleRef->W * 127.5f;

			memcpy(*trans, &newTrans, sizeof(Vector4));
			memcpy(*scale, &newScale, sizeof(Vector4));
			return changed;
		}
		else if (elemType == ElementType::UByte) {
			// Multiply by the types max value, as a float

			newScale.X = scaleRef->X * 255.0f;
			newScale.Y = scaleRef->Y * 255.0f;
			newScale.Z = scaleRef->Z * 255.0f;
			newScale.W = scaleRef->W * 255.0f;

			memcpy(*scale, &newScale, sizeof(Vector4));
			return changed;
		}
		else if (elemType == ElementType::Half || elemType == ElementType::Float || elemType == ElementType::None) {
			// These types are already floats, dont need to do any calclulation here.
			return changed;
		}

		return changed;
	}

	int VertexBuffer::SetVerticies(float* vertexBuffer, int vertexBufferSz, int to, int from) {
		UNIMPLEMENTED();
	}

	int VertexBuffer::SetVerticies(int stream, float* vertexBuffer, int vertexBufferSz, int offset, int stride, VertexFormat format, Vector4* trans, Vector4* scale, int to, int from, int count) {
		// is the vertex buffer not null?
		if (vertexBuffer == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		// is selected stream actually in the stream set?
		if (stream < 0 || stream >= static_cast<int>(this->VertexFormats.size())) return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		// is the format valid?
		if (!GetFormatIsValid(format)) return PSM_ERROR_COMMON_ARGUMENT;

		// Get format for this specific stream
		VertexFormat streamCurrentFormat = VertexFormats[stream];

		// normalize scale/trans ..
		translationScaleNormalize(streamCurrentFormat, &format, &trans, &scale);
		
		if (format == VertexFormat::None) {
			ExceptionInfo::AddMessage("Incompatible format with vertex stream\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		// get the format size
		int formatVectorSize = GetFormatVectorSize(format);
		if (!stride) // if vector is 0 
			stride = formatVectorSize;

		// check the from/to is within the range of the vertex array
		if (to < 0 || from < 0 || count < 0 || offset < 0 || count + to > this->VertexCount || stride < formatVectorSize) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		// check vertex array is big enough
		if (vertexBufferSz < (formatVectorSize + offset + (count + from - 1) * stride)) {
			ExceptionInfo::AddMessage("Vertex array is smaller than required\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		// check the offset is properly aligned to the element size
		int elmSz = GetFormatElementSize(format) - 1;
		if ((elmSz & offset) != 0 || (elmSz & stride) != 0) {
			ExceptionInfo::AddMessage("Offset or stride is not aligned properly\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		return PSM_ERROR_NO_ERROR;
	}

	VertexBuffer::VertexBuffer(int vertexCount, int indexCount, int instDivisor, int option, VertexFormat* vertexFormats, int vertexFormatsLen) {
		if (Thread::IsMainThread()) {
			if (!GraphicsContext::UniqueObjectExists()) {
				this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
				return;
			}

			// Get graphics context
			std::shared_ptr<GraphicsContext> ctx = GraphicsContext::UniqueObject();

			// Store state passed to parameters
			this->VertexCount = vertexCount;
			this->NumStreams = instDivisor;
			this->Option = option;
			this->IndexCount = indexCount;


			// Check arguments are valid

			// is vertexFormats null, or less than 0 formats?
			if (vertexFormats == nullptr && vertexFormatsLen > 0) {
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
			if (option != 0) {
				this->SetError(PSM_ERROR_COMMON_ARGUMENT);
				return;
			}

			int extensions = ctx->CapsState->Extension;
			if (instDivisor && (extensions & GraphicsExtension::InstancedArrays) == 0) {
				ExceptionInfo::AddMessage("Unsupported extension on this device\n");
				this->SetError(PSM_ERROR_COMMON_NOT_SUPPORTED);
				return;
			}

			while (glGetError()) {};

			glGenBuffers(1, &this->GLHandle);

			size_t sz = 0;

			// Determine required buffer size
			for (int i = 0; i < vertexFormatsLen; i++) {
				VertexFormat format = vertexFormats[i];

				int versionFormatSz = this->GetFormatVectorSize(format);

				// handle errors
				if (this->GetError() != PSM_ERROR_NO_ERROR)
					return;

				if (versionFormatSz > 0)
					sz += versionFormatSz;

				this->VertexFormats.push_back(format);
			}

			sz *= this->VertexCount;

			this->Size = sz;

			// Allocate array buffer in opengl.

			OpenGL::SetVertexBuffer(this);
			glBufferData(GL_ARRAY_BUFFER, sz, 0, GL_STATIC_DRAW);
			OpenGL::SetVertexBuffer(NULL);

			if (glGetError() == GL_OUT_OF_MEMORY) {
				this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
				return;
			}


		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			this->SetError(PSM_ERROR_COMMON_INVALID_OPERATION);
		}
	}

}
