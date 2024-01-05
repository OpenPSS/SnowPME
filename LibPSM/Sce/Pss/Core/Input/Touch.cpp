#include "Touch.hpp"

namespace Sce::Pss::Core::Input {
	int Touch::GetDataNative(int deviceIndex, TouchData* touchData, int numElements, int* numFinger) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Touch::GetRearTouchDataNative(int deviceIndex, TouchData* touchData, int numElements, int* numFinger) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
