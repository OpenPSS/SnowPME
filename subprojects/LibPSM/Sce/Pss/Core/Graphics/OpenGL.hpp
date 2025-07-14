#ifndef LIB_PSS_OPENGL
#define LIB_PSS_OPENGL 1

#include <Sce/Pss/Core/Graphics/Texture.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/VertexBuffer.hpp>
#include <Sce/Pss/Core/Graphics/FrameBuffer.hpp>

namespace Sce::Pss::Core::Graphics {

	class OpenGL {
	private:
		static VertexBuffer* activeVertexBuffer;
		static FrameBuffer* activeFrameBuffer;
		static ShaderProgram* activeShaderProgram;
		static Texture* activeTexture;

		static const GLenum glFormatTypes[0x10];


	public:

		static void SetShaderProgram(ShaderProgram* shaderProgram);
		static void SetVertexBuffer(VertexBuffer* vertexBuffer);
		static void SetFrameBuffer(FrameBuffer* frameBuffer);
		static void SetTexture(Texture* texture);

		static GLenum GetVertexFormatType(VertexFormat fmt);
		static GLenum GetVertexFormatNormalize(VertexFormat fmt);

	};

}

#endif