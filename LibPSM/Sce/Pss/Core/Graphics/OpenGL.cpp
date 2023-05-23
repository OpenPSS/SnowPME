#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <glad/glad.h>
namespace Sce::Pss::Core::Graphics {

	ShaderProgram* OpenGL::activeShaderProgram = nullptr;
	VertexBuffer* OpenGL::activeVertexBuffer = nullptr;
	FrameBuffer* OpenGL::activeFrameBuffer = nullptr;
	Texture* OpenGL::activeTexture = nullptr;



	void OpenGL::SetShaderProgram(ShaderProgram* shaderProgram) {
		OpenGL::activeShaderProgram = shaderProgram;
		if (shaderProgram == NULL) {
			glUseProgram(0);
		}
		else {
			int oglProgram = shaderProgram->GlReference();
			glUseProgram(oglProgram);
		}
	}

	void OpenGL::SetVertexBuffer(VertexBuffer* vertexBuffer) {
		OpenGL::activeVertexBuffer = vertexBuffer;
		if (vertexBuffer == NULL) {
			glBindBuffer(GL_ARRAY_BUFFER, NULL);
		}
		else {
			int oglBuffer = vertexBuffer->GlReference();
			glBindBuffer(GL_ARRAY_BUFFER, oglBuffer);
		}
	}

	void OpenGL::SetFrameBuffer(FrameBuffer* frameBuffer) {
		OpenGL::activeFrameBuffer = frameBuffer;
		if (frameBuffer == NULL) {
			glBindBuffer(GL_FRAMEBUFFER, NULL);
		}
		else {
			int oglBuffer = frameBuffer->GlReference();
			glBindBuffer(GL_FRAMEBUFFER, oglBuffer);
		}
	}

	void OpenGL::SetTexture(Texture* texture) {
		OpenGL::activeTexture = texture;
		if (texture == NULL) {
			glBindTexture(GL_TEXTURE_2D, NULL);
		}
		else {
			int oglBuffer = texture->GlReference();
			int oglTextureType = texture->GlTextureType();
			glBindTexture(oglTextureType, oglBuffer);
		}
	}

}