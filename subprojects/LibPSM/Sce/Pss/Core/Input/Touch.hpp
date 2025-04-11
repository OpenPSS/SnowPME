#ifndef LIB_PSS_TOUCH_H
#define LIB_PSS_TOUCH_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "TouchData.hpp"


namespace Sce::Pss::Core::Input {
	class Touch {
	public:
		static int GetDataNative(int deviceIndex, TouchData* touchData, int numElements, int *numFinger);
		static int GetRearTouchDataNative(int deviceIndex, TouchData* touchData, int numElements, int *numFinger);
	};
}
#endif
