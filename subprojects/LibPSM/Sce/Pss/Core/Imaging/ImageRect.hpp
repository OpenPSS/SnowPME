#ifndef LIB_PSS_IMAGERECT_H
#define LIB_PSS_IMAGERECT_H
#include <string>

namespace Sce::Pss::Core::Imaging {
	typedef struct ImageRect {
		int X;
		int Y;
		int Width;
		int Height;
	} ImageRect;
}

#endif