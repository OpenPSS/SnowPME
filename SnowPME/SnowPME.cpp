#include <Program.hpp>

int main(int argc, char* argv[])
{
	std::unique_ptr<SnowPME::Program> prog = std::make_unique<SnowPME::Program>(argc, argv);
	exit(prog->ExitCode());

	return -1;
}
