#ifndef LIB_PSM_FONT_H
#define LIB_PSM_FONT_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include "FontAlias.hpp"
#include "FontStyle.hpp"
#include "FontMetrics.hpp"
#include "CharMetrics.hpp"

using namespace std;

namespace Sce::PlayStation::Core::Imaging {
	class Font {
	public:
		static int NewFromFilenameSizeStyle(string filename, int size, FontStyle style, int *handle);
		static int NewFromAliasSizeStyle(FontAlias alias, int size, FontStyle style, int *handle);
		static int AddRefNative(int handle);
		static int ReleaseNative(int handle);
		static int GetName(int handle, string *name);
		static int GetSize(int handle, int *size);
		static int GetStyle(int handle, FontStyle *style);
		static int GetMetrics(int handle, FontMetrics *fontMetrics);
		static int GetTextWidthNative(int handle, string text, int offset, int len, int *width);
		static int GetTextMetricsNative(int handle, string text, int offset, int len, CharMetrics *charMetrics);
	};
}
#endif
