#ifndef LIB_PSM_IMAGECOLOR_H
#define LIB_PSM_IMAGECOLOR_H
#include <string>

namespace Sce::PlayStation::Core::Imaging {
	typedef struct ImageColor {
		int R;
		int G;
		int B;
		int A;
	} ImageColor;
}

#endif