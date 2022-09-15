#ifndef LIB_PSM_FONT_H
#define LIB_PSM_FONT_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include "FontAlias.hpp"
#include "FontStyle.hpp"
#include "FontMetrics.hpp"
#include "CharMetrics.hpp"

namespace Sce::PlayStation::Core::Imaging {
	class Font {
	public:
		static int NewFromFilenameSizeStyle(std::string filename, int size, FontStyle style, int *handle);
		static int NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int *handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetName(int handle, std::string *name);
		static int GetSize(int handle, int *size);
		static int GetStyle(int handle, FontStyle *style);
		static int GetMetrics(int handle, FontMetrics *fontMetrics);
		static int GetTextWidthNative(int handle, std::string text, int offset, int len, int *width);
		static int GetTextMetricsNative(int handle, std::string text, int offset, int len, CharMetrics *charMetrics);
	};
}
#endif
