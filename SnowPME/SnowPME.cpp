#include <LibSnowPME.hpp>

using namespace SnowPME::Util;
using namespace SnowPME::Graphics;

namespace SnowPME {
	class Program {
	
	public:
		Program() {
			Config::ReadConfig("psm.config");
			Gui::Init();
		}
	};
}

int main(int argc, char* argv[])
{
	SnowPME::Program* program = new SnowPME::Program();
}
