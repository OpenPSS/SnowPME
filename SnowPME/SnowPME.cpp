#include "Program.hpp"

int main(int argc, char* argv[])
{
	SnowPME::Program* program = new SnowPME::Program(argc, argv);
	delete program;
	return 0;
}
