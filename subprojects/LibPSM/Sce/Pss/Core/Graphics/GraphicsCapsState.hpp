#ifndef LIB_PSS_GRAPHICSCAPSSTATE_H
#define LIB_PSS_GRAPHICSCAPSSTATE_H
#include <string>

namespace Sce::Pss::Core::Graphics {
	typedef struct GraphicsCapsState {
		int Extension;
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