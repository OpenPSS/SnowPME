#ifndef LIB_PSM_IMAGERECT_H
#define LIB_PSM_IMAGERECT_H
#include <string>

namespace Sce::PlayStation::Core::Imaging {
	typedef struct ImageRect {
		int X;
		int Y;
		int Width;
		int Height;
	} ImageRect;
}

#endif