#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <glad/glad.h>
namespace Sce::Pss::Core::Graphics {

	const GLenum OpenGL::glFormatTypes[0x10] = { GL_ZERO, GL_FLOAT, GL_HALF_FLOAT_OES, GL_ZERO, GL_ZERO, GL_ZERO, GL_SHORT, GL_UNSIGNED_SHORT,
												GL_BYTE, GL_UNSIGNED_BYTE, GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO, GL_ZERO };

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

	void OpenGL::SetTexture(Texture* texture) {
		OpenGL::activeTexture = texture;
		if (texture == nullptr) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			glBindTexture(texture->GLPixelBufferType(), texture->GLHandle);
		}
	}

	GLenum OpenGL::GetVertexFormatType(VertexFormat fmt) {
		return OpenGL::glFormatTypes[static_cast<int>(fmt >> 0x8 & 0xF)];
	}
	
	// what the hell is this doing
	// can we clean this up a bit more?
	GLenum OpenGL::GetVertexFormatNormalize(VertexFormat fmt) {
		return static_cast<GLenum>((fmt >> 0xC) & 0x1);
	}

}