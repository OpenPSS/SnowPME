#include <Windowing/WindowControl.hpp>
#include <Windowing/RunFunction.hpp>

#include <cstdlib>
#include <cstring>

using namespace Shared::Debug;
namespace Shared::Windowing {

	void     (*WindowControl::swapBufferCallback)(void) = nullptr;
	uint64_t (*WindowControl::getTimeCallback)(void) = nullptr;
	void     (*WindowControl::startFrameCallback)(void);
	void     (*WindowControl::endFrameCallback)(void);
	bool     (*WindowControl::showYesNoDialogCallback)(const char*, const char*) = nullptr;

	void WindowControl::Init(void (*swapBuffers)(void),
							uint64_t(*getTime)(void),
							void(*startFrameCallback)(void),
							void(*endFrameCallback)(void),
							bool (*showYesNoDialogCallback)(const char*, const char*)) {
		
		swapBufferCallback = swapBuffers;
		getTimeCallback = getTime;
		showYesNoDialogCallback = showYesNoDialogCallback;

		isInitalized = true;
	}

	int WindowControl::SwapBuffers() {
		errorOnNotInitalized();
		swapBufferCallback();
		return 0;
	}

	uint64_t WindowControl::GetTime() {
		errorOnNotInitalized();
		return getTimeCallback();
	}


	void WindowControl::StartFrame() {
		errorOnNotInitalized();
		return startFrameCallback();
	}
	void WindowControl::EndFrame() {
		errorOnNotInitalized();
		return endFrameCallback();
	}

	bool WindowControl::YesNoDialog(const std::string& message, const std::string& caption) {
		errorOnNotInitalized();
		return showYesNoDialogCallback(message.c_str(), caption.c_str());
	}

	uintptr_t WindowControl::RunOnMainThread(uintptr_t(*ptr)(uintptr_t, uintptr_t, uintptr_t, uintptr_t), uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3) {
		RunFunction function;
		function.functionPointer = ptr;
		function.arg0 = arg0;
		function.arg1 = arg1;
		function.arg2 = arg2;
		function.arg3 = arg3;

		std::shared_ptr<Event> response = EventQueue::DispatchEvent(std::make_shared<Event>(EventType::RunFunction));
		return reinterpret_cast<uintptr_t*>(response->ArgsArray())[0];
	}

	Capture WindowControl::CaptureWindowState() {
		Capture capture;

		std::shared_ptr<Event> response = EventQueue::DispatchEvent(std::make_shared<Event>(EventType::Capture));
		memcpy(&capture, response->ArgsArray(), sizeof(Capture));

		return capture;
	}

}