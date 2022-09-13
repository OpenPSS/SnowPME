
#include <iostream>
#include "Config.hpp"
#include "Mono/Init.hpp"
using namespace SnowPME::Mono;

namespace SnowPME {
	class Program {
	public:
		Program() {
			//Config::ReadConfig("psm.config");
			Init::InitMono("Application\\app.exe");
		}
	};
}

int main()
{
	SnowPME::Program* program = new SnowPME::Program();
}
