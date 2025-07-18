#ifndef LIB_PSS_IMAGECOLOR_H
#define LIB_PSS_IMAGECOLOR_H
#include <string>
#include <cstdint>

namespace Sce::Pss::Core::Imaging {
	typedef struct ImageColor {
		int R;
		int G;
		int B;
		int A;

		inline uint32_t ToUint32() {
			return (this->R | ((this->G | ((this->B | (this->A << 8)) << 8)) << 8));
		}

	} ImageColor;

}

#endif