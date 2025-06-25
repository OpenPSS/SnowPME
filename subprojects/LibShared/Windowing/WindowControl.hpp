#ifndef SHARED_WINDOWCALLBACKS_H
#define SHARED_WINDOWCALLBACKS_H 1
#include <Windowing/WindowControl.hpp>
#include <Windowing/CallbackBase.hpp>
#include <Windowing/Capture.hpp>
#include <Windowing/EventQueue.hpp>

#include <string>

namespace Shared::Windowing {
	class WindowControl : public CallbackBase {
	private:
		static void (*swapBufferCallback)(void);
		static uint64_t (*getTimeCallback)(void);
		static bool (*showYesNoDialogCallback)(const char*, const char*);
	public:
		static void Init(void (*swapBuffers)(void),
						uint64_t(*getTime)(void),
						bool (*showYesNoDialogCallback)(const char*, const char*));

		static int SwapBuffers();
		static uint64_t GetTime();
		static bool YesNoDialog(const std::string& message, const std::string& caption);

		static Capture CaptureWindowState();

	};

}

#endif