#ifndef LIB_PSS_WINDOWSYSTEMCALLBACKS_H
#define LIB_PSS_WINDOWSYSTEMCALLBACKS_H 1
#include <string>

namespace Sce::Pss::Core::Graphics {
	class WindowSystemCallbacks {
	private:
		static bool isInitalized;
		static void (*swapBufferCallback)(void);
		static double (*getTimeCallback)(void);
		static void (*pollEventsCallback)(void);
		static bool (*wasClosedCallback)(void);
		static bool (*wasMinimizedCallback)(void);
		static bool (*showYesNoDialogCallback)(const char*, const char*);
	public:
		static void Init(void (*swapBuffers)(void),
			double (*getTime)(void),
			void (*pollEventsCallback)(void),
			bool (*wasClosedCallback)(void),
			bool (*wasMinimizedCallback)(void),
			bool (*showYesNoDialogCallback)(const char*, const char*));

		static int SwapBuffers();
		static double GetTime();
		static void PollEvents();
		static bool IsClosed();
		static bool IsMinimized();
		static bool YesNoDialog(std::string message, std::string caption);
	};

}

#endif