#ifndef SHARED_CAPTURE_H
#define SHARED_CAPTURE_H 1
#include <cstdint>
#include <mutex>

namespace Shared::Windowing {
	typedef struct Capture {
		// Window State ..
		bool Closed = false;
		bool Minmized = false;
		bool Maximized = false;
		bool Restored = true;
		bool Focused = true;

		// Controller ..
		bool CtrlCross = false;
		bool CtrlCircle = false;
		bool CtrlTriangle = false;
		bool CtrlSquare = false;

		bool CtrlLeft = false;
		bool CtrlRight = false;
		bool CtrlUp = false;
		bool CtrlDown = false;

		bool CtrlStart = false;
		bool CtrlSelect = false;

		bool CtrlR1 = false;
		bool CtrlR2 = false;
		bool CtrlL1 = false;
		bool CtrlL2 = false;

		float CtrlLAnalogX = 0.0f;
		float CtrlLAnalogY = 0.0f;

		float CtrlRAnalogX = 0.0f;
		float CtrlRAnalogY = 0.0f;

		// Touch
		int TouchX = 0;
		int TouchY = 0;
		bool TouchActive = false;

	} Capture;
};

#endif