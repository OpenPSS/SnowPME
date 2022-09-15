#ifndef LIB_PSM_GAMEPADBUTTONS_H
#define LIB_PSM_GAMEPADBUTTONS_H

namespace Sce::PlayStation::Core::Input {
	enum class GamePadButtons : unsigned int {
		Left = 0x01,
		Up = 0x02,
		Right = 0x04,
		Down = 0x08,
		Square = 0x10,
		Triangle = 0x20,
		Circle = 0x40,
		Cross = 0x80,
		Start = 0x100,
		Select = 0x200,
		L = 0x400,
		R = 0x800,
		Enter = 0x10000,
		Back = 0x20000
	};
}

#endif