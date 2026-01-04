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

	void OpenGL::SetVertexBuffer(VertexBuffer* vertexBuffer) {
		OpenGL::activeVertexBuffer = vertexBuffer;
		if (vertexBuffer == nullptr) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GLHandle);
		}
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
	GLenum OpenGL::GetVertexFormatNormalize(VertexFormat fmt) {
		return static_cast<GLenum>((fmt >> 0xC) & 0x1);
	}

	GLenum OpenGL::GetVertexFormatType(VertexFormat fmt) {
		return OpenGL::glFormatTypes[static_cast<int>(fmt >> 0x8 & 0xF)];
	}

	GLenum OpenGL::GetTextureFormatComponent(PixelFormat fmt) {
		return OpenGL::glTextureFormatComponents[static_cast<int>(fmt & 0x1F)];
	}
	GLenum OpenGL::GetTextureFormatType(PixelFormat fmt) {
		return OpenGL::glFormatTypes[static_cast<int>(fmt & 0x1F)];
	}

}