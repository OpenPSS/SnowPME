#include "Touch.hpp"

namespace Sce::PlayStation::Core::Input {
	int Touch::GetDataNative(int deviceIndex, TouchData* touchData, int numElements, int* numFinger) {
		cout << "Sce::PlayStation::Core::Input::GetDataNative(int, Sce::PlayStation::Core::Input::TouchData*, int, int *) Unimplemented." << endl;
		return 0;
	}
	int Touch::GetRearTouchDataNative(int deviceIndex, TouchData* touchData, int numElements, int* numFinger) {
		cout << "Sce::PlayStation::Core::Input::GetRearTouchDataNative(int, Sce::PlayStation::Core::Input::TouchData*, int, int *) Unimplemented." << endl;
		return 0;
	}
}
