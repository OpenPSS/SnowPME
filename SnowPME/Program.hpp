#ifndef SNOW_PME_PROGRAM_H
#define SNOW_PME_PROGRAM_H 1
#include <string>
#include <LibSnowPME.hpp>
namespace SnowPME {
	class Program {
	private:
		Graphics::Window* window;
		Graphics::Gui::SnowGui* gui;
		void startMonoApplication(std::string gamePath);
	public:
		Program();
		~Program();
	};

}

#endif