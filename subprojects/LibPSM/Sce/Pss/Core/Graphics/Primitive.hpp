#ifndef LIB_PSS_PRIMITIVE_H
#define LIB_PSS_PRIMITIVE_H
#include <string>
#include "DrawMode.hpp"

namespace Sce::Pss::Core::Graphics {
	typedef struct Primitive {
		DrawMode Mode;
		unsigned short First;
		unsigned short Count;
		unsigned short UserData;
	} Primitive;
}

#endif