#ifndef LIB_PSM_GRAPHICSUPDATE_H
#define LIB_PSM_GRAPHICSUPDATE_H

namespace Sce::PlayStation::Core::Graphics {
	enum GraphicsUpdate : unsigned int {
		None = 0,
		Enable = 1,
		Scissor = 2,
		Viewport = 4,
		DepthRange = 8,
		ClearColor = 16,
		ClearDepth = 32,
		ClearStencil = 64,
		CullFace = 128,
		BlendFunc = 256,
		DepthFunc = 512,
		PolygonOffset = 1024,
		StencilFunc = 2048,
		StencilOp = 4096,
		ColorMask = 8192,
		LineWidth = 16384,
		ShaderProgram = 16777216,
		FrameBuffer = 33554432,
		VertexBuffer = 805306368,
		Texture = 3221225472,
		VertexBuffer0 = 268435456,
		VertexBufferN = 536870912,
		Texture0 = 1073741824,
		TextureN = 2147483648
	};
}

#endif