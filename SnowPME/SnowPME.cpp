#include <LibSnowPME.hpp>

using namespace SnowPME::Runtime;
using namespace SnowPME::IO;
using namespace SnowPME::Util;
using namespace SnowPME::Graphics;

namespace SnowPME {
	class Program {
	private:
		Window* snowPmeWindow;
	public:
		Program() {
			Config::ReadConfig("psm.config");
			snowPmeWindow = new Window(Config::ScreenHeight(0), Config::ScreenWidth(0), "- SnowPME -");

			Init::LoadApplication("Test");
			Init::StartApplication();
		}
	};
}

int main()
{
	SnowPME::Program* program = new SnowPME::Program();
}
