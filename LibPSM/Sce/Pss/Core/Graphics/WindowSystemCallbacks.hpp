#ifndef LIB_PSM_WINDOWSYSTEMCALLBACKS_H
#define LIB_PSM_WINDOWSYSTEMCALLBACKS_H 1

namespace Sce::Pss::Core::Graphics {
	class WindowSystemCallbacks {
	private:
		static bool isInitalized;
		static void (*swapBufferCallback)(void);
		static double (*getTimeCallback)(void);
	public:
		static void Init(void (*swapBuffers)(void), double (*getTime)(void));
		static int SwapBuffers();
		static double GetTime();
	};

}

#endif