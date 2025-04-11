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
	using namespace Sce::Pss::Core::Imaging;
	using namespace Sce::Pss::Core;

	typedef struct GraphicsState {
		EnableMode Enable; 
		ImageRect Scissor;
		ImageRect Viewport;
		Vector2 DepthRange;
		Vector4 ClearColor;
		float ClearDepth;
		int ClearStencil;
		Sce::Pss::Core::Graphics::CullFace CullFace;
		Sce::Pss::Core::Graphics::BlendFunc BlendFuncRgb;
		Sce::Pss::Core::Graphics::BlendFunc BlendFuncAlpha;
		Sce::Pss::Core::Graphics::DepthFunc DepthFunc;
		Sce::Pss::Core::Graphics::PolygonOffset PolygonOffset;
		Sce::Pss::Core::Graphics::StencilFunc StencilFuncFront;
		Sce::Pss::Core::Graphics::StencilOp StencilOpFront;
		Sce::Pss::Core::Graphics::StencilFunc StencilFuncBack;
		Sce::Pss::Core::Graphics::StencilOp StencilOpBack;
		Sce::Pss::Core::Graphics::ColorMask ColorMask;
		float LineWidth;
	} GraphicsState;
}

#endif