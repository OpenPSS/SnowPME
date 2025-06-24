#ifndef SNOW_PME_WINDOWIMPL_H
#define SNOW_PME_WINDOWIMPL_H 1
#include <Graphics/Window.hpp>
#include <Callback/Impl.hpp>
#include <memory>

namespace SnowPME::Callback {

	class WindowImpl : public Impl {
	private:
	public:
		static void SwapBuffers();
		static double GetTime();
		static void PollEvents();
		static bool WasMinimized();
		static bool WasClosed();
		static bool YesNoMessageBox(const char* message, const char* caption);
	};


}

#endif