#ifndef SNOW_PME_RUNTIME_INIT_H
#define SNOW_PME_RUNTIME_INIT_H 1
#include <string>
#include <Graphics/Window.hpp>
#include <thread>
#include <memory>
#include <atomic>
#include <LibShared.hpp>

namespace SnowPME::Runtime
{
	class Application {
	private:
		static std::string appMainDirectory;
		static std::thread appThread;
		static std::atomic<bool> isRunning;

		static void initCallbacks(std::shared_ptr<SnowPME::Graphics::Window> window);

	public:
		static int RunPssMain();
		static void RunPssTerminate();
		static bool IsRunning();
		static int LoadApplication(const std::string& gameFolder);
	};
}

#endif