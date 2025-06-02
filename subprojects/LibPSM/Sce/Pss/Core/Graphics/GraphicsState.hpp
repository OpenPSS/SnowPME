#ifndef LIB_PSS_GRAPHICSSTATE_H
#define LIB_PSS_GRAPHICSSTATE_H
#include <string>
#include <Sce/Pss/Core/Graphics/DepthFunc.hpp>
#include <Sce/Pss/Core/Graphics/BlendFunc.hpp>
#include <Sce/Pss/Core/Graphics/ColorMask.hpp>
#include <Sce/Pss/Core/Graphics/StencilOp.hpp>
#include <Sce/Pss/Core/Graphics/StencilFunc.hpp>
#include <Sce/Pss/Core/Graphics/PolygonOffset.hpp>
#include <Sce/Pss/Core/Graphics/EnableMode.hpp>
#include <Sce/Pss/Core/Graphics/CullFace.hpp>
#include <Sce/Pss/Core/Imaging/ImageRect.hpp>
#include <Sce/Pss/Core/Vector4.hpp>
#include <Sce/Pss/Core/Vector2.hpp>


namespace Sce::Pss::Core::Graphics {

	typedef struct GraphicsState {
		EnableMode enable; 
		Sce::Pss::Core::Imaging::ImageRect scissor;
		Sce::Pss::Core::Imaging::ImageRect viewport;
		Vector2 depthRange;
		Vector4 clearColor;
		float clearDepth;
		int clearStencil;
		CullFace cullFace;
		BlendFunc blendFuncRgb;
		BlendFunc blendFuncAlpha;
		DepthFunc depthFunc;
		PolygonOffset polygonOffset;
		StencilFunc stencilFuncFront;
		StencilOp stencilOpFront;
		StencilFunc stencilFuncBack;
		StencilOp stencilOpBack;
		ColorMask colorMask;
		float lineWidth;
	} GraphicsState;
}

#endif