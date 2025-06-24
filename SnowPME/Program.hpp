#ifndef SNOW_PME_PROGRAM_H
#define SNOW_PME_PROGRAM_H 1
#include <string>
#include <LibSnowPME.hpp>
#include <memory>
#include <string>
#include <atomic>

namespace SnowPME {
	class Program {
	private:
		void progThreadFunc();
		void guiThreadFunc();
		std::atomic<bool> threadRunning = false;
		std::atomic<int> exitCode = 0;

		std::string programPath;
		std::thread guiThread;
		std::unique_ptr<SnowPME::Graphics::Gui::SnowGui> gui;
	public:
		Program(int argc, const char* const* argv);
		~Program();
		int ExitCode();
	};

}

#endif