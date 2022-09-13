#ifndef LIB_PSM_GAMEPADDATA_H
#define LIB_PSM_GAMEPADDATA_H
#include "GamePadButtons.hpp"
namespace Sce::PlayStation::Core::Input {
	typedef struct GamePadData {
		bool Skip;
		GamePadButtons Buttons;
		GamePadButtons ButtonsPrev;
		GamePadButtons ButtonsDown;
		GamePadButtons ButtonsUp;
		float AnalogLeftX;
		float AnalogLeftY;
		float AnalogRightX;
		float AnalogRightY;
	} GamePadData;
}

#endif