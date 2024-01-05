#ifndef LIB_PSS_GAMEPADDATA_H
#define LIB_PSS_GAMEPADDATA_H
#include <Sce/Pss/Core/Input/GamePadButtons.hpp>
namespace Sce::Pss::Core::Input {
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