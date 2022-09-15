#ifndef LIB_PSM_MATRIX4_H
#define LIB_PSM_MATRIX4_H
#include <string>

namespace Sce::PlayStation::Core {
	typedef struct Matrix4 {
		float M11;
		float M12;
		float M13;
		float M14;
		float M21;
		float M22;
		float M23;
		float M24;
		float M31;
		float M32;
		float M33;
		float M34;
		float M41;
		float M42;
		float M43;
		float M44;
	} Matrix4;
}

#endif