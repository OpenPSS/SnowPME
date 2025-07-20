#ifndef LIB_PSS_GRAPHICSCAPSSTATE_H
#define LIB_PSS_GRAPHICSCAPSSTATE_H
#include <string>
#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>

namespace Sce::Pss::Core::Graphics {
	typedef struct GraphicsCapsState {
		GraphicsExtension Extension = GraphicsExtension::None;
		int MaxViewportWidth = 0;
		int MaxViewportHeight = 0;
		int MaxTextureSize = 0;
		int MaxCubeMapTextureSize = 0;
		int MaxRenderbufferSize = 0;
		int MaxVertexUniformVectors = 0;
		int MaxFragmentUniformVectors = 0;
		int MaxVertexAttribs = 0;
		int MaxVaryingVectors = 0;
		int MaxCombinedTextureImageUnits = 0;
		int MaxTextureImageUnits = 0;
		int MaxVertexTextureImageUnits = 0;
		float MaxTextureMaxAnisotropy = 0.0f;
		float MinAliasedLineWidth = 0.0f;
		float MaxAliasedLineWidth = 0.0f;
		float MinAliasedPointSize = 0.0f;
		float MaxAliasedPointSize = 0.0f;
	} GraphicsCapsState;
}

#endif