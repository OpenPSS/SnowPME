#include <Util/Config.hpp>
#include <Runtime/Init.hpp>
#include <Io/Path.hpp>

using namespace SnowPME::Runtime;
using namespace SnowPME::Io;
using namespace SnowPME::Util;

namespace SnowPME {
	class Program {
	public:
		Program() {
			Config::ReadConfig("psm.config");
			Init::InitMono("Application\\app.exe");
		}
	};
}

int main()
{
	SnowPME::Program* program = new SnowPME::Program();
}
