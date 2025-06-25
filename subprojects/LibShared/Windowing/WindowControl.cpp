#include <Windowing/WindowControl.hpp>
#include <cstdlib>
#include <cstring>

namespace Shared::Windowing {
	using namespace Shared::Debug;

	void   (*WindowControl::swapBufferCallback)(void) = nullptr;
	uint64_t (*WindowControl::getTimeCallback)(void) = nullptr;
	bool   (*WindowControl::showYesNoDialogCallback)(const char*, const char*) = nullptr;

	void WindowControl::Init(void (*swapBuffers)(void),
							uint64_t (*getTime)(void),
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

	bool WindowControl::YesNoDialog(const std::string& message, const std::string& caption) {
		errorOnNotInitalized();
		return showYesNoDialogCallback(message.c_str(), caption.c_str());
	}


	Capture WindowControl::CaptureWindowState() {
		Capture capture;

		std::shared_ptr<Event> response = EventQueue::DispatchEvent(std::make_shared<Event>(EventType::Capture));
		memcpy(&capture, response->ArgsArray(), sizeof(Capture));

		return capture;
	}

}