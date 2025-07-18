#ifndef LIB_PSS_FONT_H
#define LIB_PSS_FONT_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include <Sce/Pss/Core/Imaging/FontAlias.hpp>
#include <Sce/Pss/Core/Imaging/FontStyle.hpp>
#include <Sce/Pss/Core/Imaging/FontMetrics.hpp>
#include <Sce/Pss/Core/Imaging/CharMetrics.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Imaging {
	class Font {
	public:
		static int NewFromFilenameSizeStyle(MonoString* filename, int size, FontStyle style, int *handle);
		static int NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int *handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetName(int handle, MonoString *name);
		static int GetSize(int handle, int *size);
		static int GetStyle(int handle, FontStyle *style);
		static int GetMetrics(int handle, FontMetrics *fontMetrics);
		static int GetTextWidthNative(int handle, MonoString* text, int offset, int len, int *width);
		static int GetTextMetricsNative(int handle, MonoString* text, int offset, int len, CharMetrics *charMetrics);
	};
}
#endif
