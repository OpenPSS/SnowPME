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
		static void(*startFrameCallback)(void);
		static void(*endFrameCallback)(void);
		static bool (*showYesNoDialogCallback)(const char*, const char*);
		static std::string (*getBackend)(void);

	public:
		static void Init(void (*swapBuffers)(void),
						uint64_t(*getTime)(void),
						void(*startFrameCallback)(void),
						void(*endFrameCallback)(void),
						bool (*showYesNoDialogCallback)(const char*, const char*),
						std::string (*isGles)(void));

		static std::string GetBackend();
		static int SwapBuffers();
		static uint64_t GetTime();
		static void StartFrame();
		static void EndFrame();
		static bool YesNoDialog(const std::string& message, const std::string& caption);
		static uintptr_t RunOnMainThread(uintptr_t(*ptr)(uintptr_t, uintptr_t, uintptr_t, uintptr_t), uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3);
		static Capture CaptureWindowState();

	};

}

#endif