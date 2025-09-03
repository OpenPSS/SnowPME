#include <Windowing/WindowControl.hpp>
#include <Windowing/RunFunction.hpp>

#include <cstdlib>
#include <cstring>

using namespace Shared::Debug;
namespace Shared::Windowing {

	void		 (*WindowControl::swapBufferCallback)(void) = nullptr;
	uint64_t	 (*WindowControl::getTimeCallback)(void) = nullptr;
	void		 (*WindowControl::startFrameCallback)(void);
	void		 (*WindowControl::endFrameCallback)(void);
	bool		 (*WindowControl::showYesNoDialogCallback)(const char*, const char*) = nullptr;
	std::string	 (*WindowControl::getBackend)(void) = nullptr;

	void WindowControl::Init(void (*swapBuffers)(void),
							uint64_t(*getTime)(void),
							void(*startFrameCallback)(void),
							void(*endFrameCallback)(void),
							bool (*showYesNoDialogCallback)(const char*, const char*),
							std::string (*getBackend)(void)) {
		
		WindowControl::swapBufferCallback = swapBuffers;
		WindowControl::getTimeCallback = getTime;
		WindowControl::showYesNoDialogCallback = showYesNoDialogCallback;
		WindowControl::startFrameCallback = startFrameCallback;
		WindowControl::endFrameCallback = endFrameCallback;
		WindowControl::getBackend = getBackend;

		isInitalized = true;
	}

	std::string WindowControl::GetBackend() {
		errorOnNotInitalized();
		return getBackend();
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
		RunFunction args;
		args.functionPointer = ptr;
		args.arg0 = arg0;
		args.arg1 = arg1;
		args.arg2 = arg2;
		args.arg3 = arg3;

		std::shared_ptr<Event> response = EventQueue::DispatchEvent(std::make_shared<Event>(EventType::RunFunction, &args, sizeof(args)));
		return reinterpret_cast<uintptr_t*>(response->ResponseArray())[0];
	}

	Capture WindowControl::CaptureWindowState() {
		Capture capture;

		std::shared_ptr<Event> response = EventQueue::DispatchEvent(std::make_shared<Event>(EventType::Capture));
		memcpy(&capture, response->ResponseArray(), sizeof(Capture));

		return capture;
	}

}