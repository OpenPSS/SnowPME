#ifndef LIB_PSM_GRAPHICSEXTENSION_H
#define LIB_PSM_GRAPHICSEXTENSION_H

namespace Sce::PlayStation::Core::Graphics {
	enum class GraphicsExtension : unsigned int {
		None = 0,
		DepthTexture = 1,
		Texture3D = 2,
		TextureNpot = 4,
		TextureFilterAnisotropic = 8,
		Rgb8Rgba8 = 16,
		Depth24 = 32,
		Depth32 = 64,
		PackedDepthStencil = 128,
		VertexHalfFloat = 256,
		Vertex1010102 = 512,
		TextureFloat = 1024,
		TextureHalfFloat = 2048,
		TextureFloatLinear = 4096,
		TextureHalfFloatLinear = 8192,
		Texture2101010Rev = 16384
	};
}

#endif