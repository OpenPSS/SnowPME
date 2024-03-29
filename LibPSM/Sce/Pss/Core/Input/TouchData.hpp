#ifndef LIB_PSS_TOUCHDATA_H
#define LIB_PSS_TOUCHDATA_H
#include "TouchStatus.hpp"

namespace Sce::Pss::Core::Input {
	typedef struct TouchData {
		bool Skip;
		int ID;
		TouchStatus Status;
		float X;
		float Y;
		int reserved0;
		int reserved1;
		int reserved2;
	} TouchData;
}

#endif