#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <glad/glad.h>
namespace Sce::Pss::Core::Graphics {

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
			glUseProgram(shaderProgram->GLReference);
		}
	}

	void OpenGL::SetVertexBuffer(VertexBuffer* vertexBuffer) {
		OpenGL::activeVertexBuffer = vertexBuffer;
		if (vertexBuffer == nullptr) {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		else {
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GLReference);
		}
	}

	void OpenGL::SetFrameBuffer(FrameBuffer* frameBuffer) {
		OpenGL::activeFrameBuffer = frameBuffer;
		if (frameBuffer == nullptr) {
			glBindBuffer(GL_FRAMEBUFFER, 0);
		}
		else {
			glBindBuffer(GL_FRAMEBUFFER, frameBuffer->GLReference);
		}
	}

	void OpenGL::SetTexture(Texture* texture) {
		OpenGL::activeTexture = texture;
		if (texture == nullptr) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else {
			glBindTexture(texture->GLTextureType(), texture->GLReference);
		}
	}

}