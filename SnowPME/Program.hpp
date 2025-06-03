#ifndef SNOW_PME_PROGRAM_H
#define SNOW_PME_PROGRAM_H 1
#include <string>
#include <LibSnowPME.hpp>
#include <memory>

namespace SnowPME {
	class Program {
	private:
		std::shared_ptr<Graphics::Window> window;
		void startMonoApplication(const std::string& gamePath);
		void startEventLoop();
	public:
		Program(int argc, const char* const* argv);
		~Program();
	};

}

#endif