#ifndef LIB_PSS_GRAPHICSEXTENSION_H
#define LIB_PSS_GRAPHICSEXTENSION_H

namespace Sce::Pss::Core::Graphics {
    enum GraphicsExtension : unsigned int {
        None = 0x0,
        DepthTexture = 0x1,
        Texture3D = 0x2,
        TextureNpot = 0x4,
        TextureFilterAnisotropic = 0x8,
        Rgb8Rgba8 = 0x10,
        Depth24 = 0x20,
        Depth32 = 0x40,
        PackedDepthStencil = 0x80,
        VertexHalfFloat = 0x100,
        Vertex1010102 = 0x200,
        TextureFloat = 0x400,
        TextureHalfFloat = 0x800,
        TextureFloatLinear = 0x1000,
        TextureHalfFloatLinear = 0x2000,
        Texture2101010Rev = 0x4000,
        TextureNPot2DMipMap = 0x8000,
        DrawInstanced = 0x10000,
        InstancedArrays = 0x20000
    };
}

#endif