#ifndef LIB_PSM_PSMGRAPHICSCONTEXT_H
#define LIB_PSM_PSMGRAPHICSCONTEXT_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include <Sce/PlayStation/Core/Graphics/DrawMode.hpp>
#include <Sce/PlayStation/Core/Graphics/PixelFormat.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsUpdate.hpp>
#include <Sce/PlayStation/Core/Graphics/ClearMask.hpp>
#include <Sce/PlayStation/Core/Graphics/TextureCubeFace.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsState.hpp>
#include <Sce/PlayStation/Core/Graphics/Primitive.hpp>
#include <Sce/PlayStation/Core/Graphics/GraphicsCapsState.hpp>
#include <Sce/PlayStation/Core/Graphics/MultiSampleMode.hpp>
#include <Sce/PlayStation/Core/Imaging/ImageSize.hpp>

#include <LibSnowPME.hpp>
#include <mono/mono.h>

using namespace SnowPME::Util;
using namespace Sce::PlayStation::Core::Imaging;



namespace Sce::PlayStation::Core::Graphics {

	class PsmGraphicsContext {
	public:
		static int Create(int width, int height, PixelFormat colorFormat, PixelFormat depthFormat, MultiSampleMode multiSampleMode, int *result);
		static int Delete(int handle);
		static int Update(int handle, GraphicsUpdate update, GraphicsState *state, int *handles);
		static int SwapBuffers(int handle);
		static int Clear(int handle, ClearMask mask);
		static int DrawArrays(int handle, DrawMode mode, int first, int count, int repeat);
		static int DrawArrays2(int handle, Primitive* primitives, int first, int count);
		static int DrawArraysInstanced(int handle, DrawMode mode, int first, int count, int instFirst, int instCount);
		static int ReadPixels(int handle, std::byte* pixels, PixelFormat format, int sx, int sy, int sw, int sh);
		static int ReadPixels2(int handle, int texture, int level, TextureCubeFace cubeFace, int dx, int dy, int sx, int sy, int sw, int sh);
		static int GetMaxScreenSize(int *width, int *height);
		static int GetScreenSizes(MonoArray* sizes, int *result);
		static int GetScreenInfo(int handle, int *width, int *height, PixelFormat *colorFormat, PixelFormat *depthFormat, MultiSampleMode *multiSampleMode);
		static int GetCaps(int handle, GraphicsCapsState *caps);
		static int SetActiveScreen(int handle, int x, int y, int w, int h);
		static int SetVirtualScreen(int handle, int x, int y, int w, int h);
	};
}
#endif
