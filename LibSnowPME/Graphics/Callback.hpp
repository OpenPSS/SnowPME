#ifndef SNOW_PME_GRAPHICSCALLBACk_H
#define SNOW_PME_GRAPHICSCALLBACk_H 1
#include <Graphics/Window.hpp>
namespace SnowPME::Graphics {

	class Callback {
	private:
		static Window* mainWindow;
		static bool isInitalized;
	public:
		static void Init(Window* oglWindow);
		static void SwapBuffers();
		static double GetTime();
		static void PollEvents();
		static bool WasMinimized();
		static bool WasClosed();
	};


}

#endif