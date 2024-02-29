#include <LibSnowPME.hpp>
#include <string>
#include <LibShared.hpp>
using namespace Shared;
using namespace SnowPME::Graphics;
using namespace SnowPME::Runtime;

namespace SnowPME {
	class Program {
	
	public:
		Program(std::string gamePath) {
			Config::ReadConfig("SnowPME.cfg");
			Init::LoadApplication(gamePath);
			Init::StartApplication();
		}
	};
}

int main(int argc, char* argv[])
{
	std::string gamePath = "psm/test";
	if (argc >= 2)
		gamePath = std::string(argv[1]);

	SnowPME::Program* program = new SnowPME::Program(gamePath);

	return 0;
}
