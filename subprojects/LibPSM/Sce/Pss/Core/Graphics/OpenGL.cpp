#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <glad/glad.h>
namespace Sce::Pss::Core::Graphics {

	const GLenum OpenGL::glFormatTypes[0x10] = { GL_NONE, GL_FLOAT, GL_HALF_FLOAT_OES, GL_NONE, GL_NONE, GL_NONE, GL_SHORT, GL_UNSIGNED_SHORT,
												GL_BYTE, GL_UNSIGNED_BYTE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE };

	const GLenum OpenGL::glTextureTypes[0x20] = { GL_NONE, GL_UNSIGNED_BYTE, GL_HALF_FLOAT_OES, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_BYTE, GL_HALF_FLOAT_OES,
												  GL_UNSIGNED_BYTE, GL_HALF_FLOAT_OES, GL_UNSIGNED_BYTE, GL_HALF_FLOAT_OES, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT,
												  GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE };

	const GLenum OpenGL::glTextureFormatComponents[0x20] = { GL_NONE, GL_RGBA, GL_RGBA, GL_RGBA, GL_RGBA, GL_RGB, GL_LUMINANCE_ALPHA, GL_LUMINANCE_ALPHA,
														   GL_LUMINANCE, GL_LUMINANCE, GL_ALPHA, GL_ALPHA, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT,
														   GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE, GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE,
														   GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE };

	ShaderProgram* OpenGL::activeShaderProgram = nullptr;
	VertexBuffer* OpenGL::activeVertexBuffer = nullptr;
	FrameBuffer* OpenGL::activeFrameBuffer = nullptr;
	Texture* OpenGL::activeTexture = nullptr;

	void OpenGL::SetShaderProgram(ShaderProgram* shaderProgram) {
		OpenGL::activeShaderProgram = shaderProgram;
		if (shaderProgram == nullptr) {
			glUseProgram(0);
		}
		else {
			glUseProgram(shaderProgram->GLHandle);
		}
	}

	VertexBuffer* OpenGL::SetVertexBuffer(VertexBuffer* vertexBuffer) {
		VertexBuffer* prev = OpenGL::activeVertexBuffer;
		OpenGL::activeVertexBuffer = vertexBuffer;
		if (vertexBuffer == nullptr) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GLHandle);
		}
		return prev;
	}

	void OpenGL::SetFrameBuffer(FrameBuffer* frameBuffer) {
		OpenGL::activeFrameBuffer = frameBuffer;
		if (frameBuffer == nullptr) {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		else {
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->GLHandle);
		}
	}

	Texture* OpenGL::SetTexture(Texture* texture) {
		Texture* previous = OpenGL::activeTexture;
		OpenGL::activeTexture = texture;
		if (texture != nullptr) {
			glBindTexture(texture->GLPixelBufferType(), texture->GLHandle);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		return previous;
	}

	
	// TODO: figure out what the hell is this doing
	// can we clean this up a bit more?
	GLenum OpenGL::GetVertexFormatNormalize(VertexFormat format) {
		return static_cast<GLenum>((format >> 0xC) & 0x1);
	}

	GLenum OpenGL::GetVertexFormatType(VertexFormat format) {
		return OpenGL::glFormatTypes[static_cast<int>(format >> 0x8 & 0xF)];
	}

	GLenum OpenGL::GetTextureFormatComponent(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return GL_NONE;
			case PixelFormat::Rgba:
				return GL_RGBA;
			case PixelFormat::RgbaH:
				return GL_RGBA;
			case PixelFormat::Rgba4444:
				return GL_RGBA;
			case PixelFormat::Rgba5551:
				return GL_RGBA;
			case PixelFormat::Rgb565:
				return GL_RGB;
			case PixelFormat::LuminanceAlpha:
				return GL_LUMINANCE_ALPHA;
			case PixelFormat::LuminanceAlphaH:
				return GL_LUMINANCE_ALPHA;
			case PixelFormat::Luminance:
				return GL_LUMINANCE;
			case PixelFormat::LuminanceH:
				return GL_LUMINANCE;
			case PixelFormat::Alpha:
				return GL_ALPHA;
			case PixelFormat::AlphaH:
				return GL_ALPHA;
			case PixelFormat::Depth16:
				return GL_DEPTH_COMPONENT;
			case PixelFormat::Depth24:
				return GL_DEPTH_COMPONENT;
			case PixelFormat::Depth16Stencil8:
				return GL_DEPTH_COMPONENT;
			case PixelFormat::Depth24Stencil8:
				return GL_DEPTH_COMPONENT;
			case PixelFormat::Dxt1:
				return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			case PixelFormat::Dxt2:
				return GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE;
			case PixelFormat::Dxt3:
				return GL_COMPRESSED_RGBA_S3TC_DXT3_ANGLE;
			case PixelFormat::Dxt4:
				return GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE;
			case PixelFormat::Dxt5:
				return GL_COMPRESSED_RGBA_S3TC_DXT5_ANGLE;
		}

		UNREACHABLE();
	}
	GLenum OpenGL::GetTextureFormatType(PixelFormat format) {
		switch (format) {
			case PixelFormat::None:
				return GL_NONE;
			case PixelFormat::Rgba:
				return GL_UNSIGNED_BYTE;
			case PixelFormat::RgbaH:
				return GL_HALF_FLOAT_OES;
			case PixelFormat::Rgba4444:
				return GL_UNSIGNED_SHORT_4_4_4_4;
			case PixelFormat::Rgba5551:
				return GL_UNSIGNED_SHORT_5_5_5_1;
			case PixelFormat::Rgb565:
				return GL_UNSIGNED_SHORT_5_6_5;
			case PixelFormat::LuminanceAlpha:
				return GL_UNSIGNED_BYTE;
			case PixelFormat::LuminanceAlphaH:
				return GL_HALF_FLOAT_OES;
			case PixelFormat::Luminance:
				return GL_UNSIGNED_BYTE;
			case PixelFormat::LuminanceH:
				return GL_HALF_FLOAT_OES;
			case PixelFormat::Alpha:
				return GL_UNSIGNED_BYTE;
			case PixelFormat::AlphaH:
				return GL_HALF_FLOAT_OES;
			case PixelFormat::Depth16:
				return GL_UNSIGNED_SHORT;
			case PixelFormat::Depth24:
				return GL_UNSIGNED_INT;
			case PixelFormat::Depth16Stencil8:
				return GL_UNSIGNED_SHORT;
			case PixelFormat::Depth24Stencil8:
				return GL_UNSIGNED_INT;
			case PixelFormat::Dxt1:
				return GL_NONE;
			case PixelFormat::Dxt2:
				return GL_NONE;
			case PixelFormat::Dxt3:
				return GL_NONE;
			case PixelFormat::Dxt4:
				return GL_NONE;
			case PixelFormat::Dxt5:
				return GL_NONE;
		}
		UNREACHABLE();
	}

}