#ifndef LIB_PSM_PSMGRAPHICSCONTEXT_H
#define LIB_PSM_PSMGRAPHICSCONTEXT_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include "DrawMode.hpp"
#include "PixelFormat.hpp"
#include "GraphicsUpdate.hpp"
#include "ClearMask.hpp"
#include "TextureCubeFace.hpp"
#include "GraphicsState.hpp"
#include "Primitive.hpp"
#include "GraphicsCapsState.hpp"
#include "MultiSampleMode.hpp"
#include "../Imaging/ImageSize.hpp"

#include <LibSnowPME.hpp>
#include <mono/mono.h>

using namespace SnowPME::Util;
using namespace Sce::PlayStation::Core::Imaging;

#define CTX_CHECK (PsmGraphicsContext::GetContext() == NULL)
#define THREAD_CHECK (AppGlobals::PsmMainThreadId() == PlatformSpecific::CurrentThreadId())


namespace Sce::PlayStation::Core::Graphics {
	typedef struct GraphicsContext {
		int Width;
		int Height;
		PixelFormat ColorFormat;
		PixelFormat DepthFormat;
		MultiSampleMode MultiSampleMode;
		GraphicsCapsState* CapsState;
		Window* MainWindow;
		std::string Extensions;
		std::string Renderer;
		uint64_t ThreadId;
		uint32_t BoundArrayBuffer;
	} GraphicsContext;

	class PsmGraphicsContext {
	public:
		static GraphicsContext* GetContext();
		static int BindArrayBuffer(uint32_t buffer);

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
