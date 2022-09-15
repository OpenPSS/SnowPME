#ifndef LIB_PSM_GRAPHICSSTATE_H
#define LIB_PSM_GRAPHICSSTATE_H
#include <string>
#include "DepthFunc.hpp"
#include "BlendFunc.hpp"
#include "ColorMask.hpp"
#include "StencilOp.hpp"
#include "StencilFunc.hpp"
#include "PolygonOffset.hpp"
#include "EnableMode.hpp"
#include "CullFace.hpp"
#include "../Imaging/ImageRect.hpp"
#include "../Vector4.hpp"
#include "../Vector2.hpp"
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