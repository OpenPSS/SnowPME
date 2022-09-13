#ifndef LIB_PSM_GRAPHICSCAPSSTATE_H
#define LIB_PSM_GRAPHICSCAPSSTATE_H
#include <string>
#include "GraphicsExtension.hpp"

namespace Sce::PlayStation::Core::Graphics {
	typedef struct GraphicsCapsState {
		GraphicsExtension Extension;
		int MaxViewportWidth;
		int MaxViewportHeight;
		int MaxTextureSize;
		int MaxCubeMapTextureSize;
		int MaxRenderbufferSize;
		int MaxVertexUniformVectors;
		int MaxFragmentUniformVectors;
		int MaxVertexAttribs;
		int MaxVaryingVectors;
		int MaxCombinedTextureImageUnits;
		int MaxTextureImageUnits;
		int MaxVertexTextureImageUnits;
		float MaxTextureMaxAnisotropy;
		float MinAliasedLineWidth;
		float MaxAliasedLineWidth;
		float MinAliasedPointSize;
		float MaxAliasedPointSize;
	} GraphicsCapsState;
}

#endif