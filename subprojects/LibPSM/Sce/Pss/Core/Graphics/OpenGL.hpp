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
		static const GLenum glTextureTypes[0x20];
		static const GLenum glTextureFormatComponents[0x20];


	public:

		static void SetShaderProgram(ShaderProgram* shaderProgram);
		static VertexBuffer* SetVertexBuffer(VertexBuffer* vertexBuffer);
		static void SetFrameBuffer(FrameBuffer* frameBuffer);

		// Returns: Previous Texture
		static Texture* SetTexture(Texture* texture);

		static GLenum GetVertexFormatType(VertexFormat fmt);
		static GLenum GetVertexFormatNormalize(VertexFormat fmt);
		
		static GLenum GetTextureFormatComponent(PixelFormat fmt);
		static GLenum GetTextureFormatType(PixelFormat fmt);


	};

}

#endif