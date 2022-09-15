#ifndef LIB_PSM_GAMEPAD_H
#define LIB_PSM_GAMEPAD_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "GamePadData.hpp"


namespace Sce::PlayStation::Core::Input {
	class GamePad {
	public:
		static int GetDataNative(int deviceIndex, GamePadData *gamePadData);
	};
}
#endif
