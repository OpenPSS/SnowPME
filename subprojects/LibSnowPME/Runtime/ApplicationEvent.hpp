#ifndef SNOW_PME_APPLICATIONEVENT_H
#define SNOW_PME_APPLICATIONEVENT_H 1
#include <Graphics/Window.hpp>
#include <LibShared.hpp>
#include <memory>
#include <mutex>
#include <atomic>
namespace SnowPME::Runtime {

	class ApplicationEvent {
	private:
		static std::mutex captureLock;
		static Shared::Windowing::Capture state;
		static std::atomic<bool> initalized;

	public:
		static void Init();
		
		static void FrameStart();
		static void FrameEnd();
		static void SwapBuffers();
		static uint64_t GetTime();
		static bool YesNoMessageBox(const char* message, const char* caption);

		static void ProcessEvent();

	};


}

#endif
