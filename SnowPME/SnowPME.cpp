#include "Program.hpp"

int main(int argc, char* argv[])
{
	static_cast<void>(argc);
	static_cast<void>(argv);
	SnowPME::Program* program = new SnowPME::Program();
	delete program;
	return 0;
}
