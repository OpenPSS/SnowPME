#ifndef SNOW_PME_APPLICATIONEVENT_H
#define SNOW_PME_APPLICATIONEVENT_H 1
#include <Graphics/Window.hpp>
#include <LibShared.hpp>
#include <memory>
#include <mutex>
namespace SnowPME::Runtime {

	class ApplicationEvent{
	private:
		static std::mutex captureLock;
		static Shared::Windowing::Capture state;

	public:
		
		static void SwapBuffers();
		static uint64_t GetTime();
		static bool YesNoMessageBox(const char* message, const char* caption);

		static void ProcessEvent();

	};


}

#endif
