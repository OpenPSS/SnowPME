#ifndef LIB_PSS_GAMEPAD_H
#define LIB_PSS_GAMEPAD_H 1
#include <string>
#include <iostream>
#include <Sce/Pss/Core/Input/GamePadData.hpp>


namespace Sce::Pss::Core::Input {
	class GamePad {
	public:
		static int GetDataNative(int deviceIndex, GamePadData *gamePadData);
	};
}
#endif
