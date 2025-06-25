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
		bool Visible = true;

		// Controller ..
		uint32_t Buttons = 0;
		float AnalogX = 0.0f;
		float AnalogY = 0.0f;

		// Touch
		uint32_t TouchX = 0;
		uint32_t TouchY = 0;
	} Capture;
};

#endif