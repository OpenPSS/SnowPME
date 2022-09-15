#include <Util/Config.hpp>
#include <Runtime/Init.hpp>
#include <Io/Path.hpp>

using namespace SnowPME::Runtime;
using namespace SnowPME::IO;
using namespace SnowPME::Util;

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
