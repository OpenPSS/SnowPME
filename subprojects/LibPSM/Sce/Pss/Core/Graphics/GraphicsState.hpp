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
		EnableMode Enable; 
		Imaging::ImageRect Scissor;
		Imaging::ImageRect Viewport;
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