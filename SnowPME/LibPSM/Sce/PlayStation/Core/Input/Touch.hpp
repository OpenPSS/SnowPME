#ifndef LIB_PSM_TOUCH_H
#define LIB_PSM_TOUCH_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TouchData.hpp"
using namespace std;

namespace Sce::PlayStation::Core::Input {
	class Touch {
	public:
		static int GetDataNative(int deviceIndex, TouchData* touchData, int numElements, int *numFinger);
		static int GetRearTouchDataNative(int deviceIndex, TouchData* touchData, int numElements, int *numFinger);
	};
}
#endif
