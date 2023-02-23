#ifndef LIB_PSM_GRAPHICSSTATE_H
#define LIB_PSM_GRAPHICSSTATE_H
#include <string>
#include <Sce/PlayStation/Core/Graphics/DepthFunc.hpp>
#include <Sce/PlayStation/Core/Graphics/BlendFunc.hpp>
#include <Sce/PlayStation/Core/Graphics/ColorMask.hpp>
#include <Sce/PlayStation/Core/Graphics/StencilOp.hpp>
#include <Sce/PlayStation/Core/Graphics/StencilFunc.hpp>
#include <Sce/PlayStation/Core/Graphics/PolygonOffset.hpp>
#include <Sce/PlayStation/Core/Graphics/EnableMode.hpp>
#include <Sce/PlayStation/Core/Graphics/CullFace.hpp>
#include <Sce/PlayStation/Core/Imaging/ImageRect.hpp>
#include <Sce/PlayStation/Core/Vector4.hpp>
#include <Sce/PlayStation/Core/Vector2.hpp>
using namespace Sce::PlayStation::Core::Imaging;
using namespace Sce::PlayStation::Core;

namespace Sce::PlayStation::Core::Graphics {
	typedef struct GraphicsState {
		EnableMode Enable; /* EnableMode */
		ImageRect Scissor;
		ImageRect Viewport;
		Vector2 DepthRange;
		Vector4 ClearColor;
		float ClearDepth;
		int ClearStencil;
		CullFace CullFace;
		BlendFunc BlendFuncRgb;
		BlendFunc BlendFuncAlpha;
		DepthFunc DepthFunc;
		PolygonOffset PolygonOffset;
		StencilFunc StencilFuncFront;
		StencilOp StencilOpFront;
		StencilFunc StencilFuncBack;
		StencilOp StencilOpBack;
		ColorMask ColorMask;
		float LineWidth;
	} GraphicsState;
}

#endif