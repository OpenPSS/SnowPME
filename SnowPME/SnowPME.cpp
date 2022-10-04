#include <LibSnowPME.hpp>

using namespace SnowPME::Runtime;
using namespace SnowPME::IO;
using namespace SnowPME::Util;
using namespace SnowPME::Graphics;

namespace SnowPME {
	class Program {
	
	public:
		Program() {
			Config::ReadConfig("psm.config");

			Init::LoadApplication("Test");
			Init::StartApplication();
		}
	};
}

int main()
{
	SnowPME::Program* program = new SnowPME::Program();
}
