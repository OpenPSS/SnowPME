#include <LibSnowPME.hpp>

using namespace SnowPME::Graphics;

namespace SnowPME {
	class Program {
	
	public:
		Program() {
			Gui::Init();
		}
	};
}

int main(int argc, char* argv[])
{
	SnowPME::Program* program = new SnowPME::Program();

	return 0;
}
