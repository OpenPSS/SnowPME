#ifndef LIB_PSS_WINDOWSYSTEMCALLBACKS_H
#define LIB_PSS_WINDOWSYSTEMCALLBACKS_H 1

namespace Sce::Pss::Core::Graphics {
	class WindowSystemCallbacks {
	private:
		static bool isInitalized;
		static void (*swapBufferCallback)(void);
		static double (*getTimeCallback)(void);
		static void (*pollEventsCallback)(void);
		static bool (*wasCloseedCallback)(void);
		static bool (*wasMinimizedCallback)(void);
	public:
		static void Init(void (*swapBuffers)(void),
			double (*getTime)(void),
			void (*pollEventsCallback)(void),
			bool (*wasCloseedCallback)(void),
			bool (*wasMinimizedCallback)(void));

		static int SwapBuffers();
		static double GetTime();
		static void PollEvents();
		static bool IsClosed();
		static bool IsMinimized();
	};

}

#endif