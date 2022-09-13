#ifndef LIB_PSM_PRIMITIVE_H
#define LIB_PSM_PRIMITIVE_H
#include <string>
#include "DrawMode.hpp"

namespace Sce::PlayStation::Core::Graphics {
	typedef struct Primitive {
		DrawMode Mode;
		unsigned short First;
		unsigned short Count;
		unsigned short UserData;
	} Primitive;
}

#endif