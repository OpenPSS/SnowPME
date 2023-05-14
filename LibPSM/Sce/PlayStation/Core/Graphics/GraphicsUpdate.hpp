#ifndef LIB_PSM_GRAPHICSUPDATE_H
#define LIB_PSM_GRAPHICSUPDATE_H

namespace Sce::PlayStation::Core::Graphics {
	enum class GraphicsUpdate : unsigned int {
		None = 0x0,
		Enable = 0x1,
		Scissor = 0x2,
		Viewport = 0x4,
		DepthRange = 0x8,
		ClearColor = 0x10,
		ClearDepth = 0x20,
		ClearStencil = 0x40,
		CullFace = 0x80,
		BlendFunc = 0x100,
		DepthFunc = 0x200,
		PolygonOffset = 0x400,
		StencilFunc = 0x800,
		StencilOp = 0x1000,
		ColorMask = 0x2000,
		LineWidth = 0x4000,
		ShaderProgram = 0x1000000,
		FrameBuffer = 0x2000000,
		Texture = 0xC0000000,
		VertexBuffer0 = 0x10000000,
		VertexBufferN = 0x20000000,
		VertexBuffer = 0x30000000,
		Texture0 = 0x40000000,
		TextureN = 0x80000000
	};

	GraphicsUpdate operator&(GraphicsUpdate l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };
	GraphicsUpdate operator&(GraphicsUpdate l, unsigned int r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };
	GraphicsUpdate operator&(unsigned int l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l & (unsigned int)r); };

	GraphicsUpdate operator|(GraphicsUpdate l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };
	GraphicsUpdate operator|(unsigned int l, GraphicsUpdate r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };
	GraphicsUpdate operator|(GraphicsUpdate l, unsigned int r) { return (GraphicsUpdate)((unsigned int)l | (unsigned int)r); };


}

#endif