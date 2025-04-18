#ifndef SNOW_PME_PROGRAM_H
#define SNOW_PME_PROGRAM_H 1
#include <string>
#include <LibSnowPME.hpp>
namespace SnowPME {
	class Program {
	private:
		Graphics::Window* window = nullptr;
		Graphics::Gui::SnowGui* gui = nullptr;
		void startMonoApplication(const std::string& gamePath);
		void startEventLoop();
	public:
		Program(int argc, const char* const* argv);
		~Program();
	};

}

#endif