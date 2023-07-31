#ifndef LIB_PSS_PROGRAMUNIFORM
#define LIB_PSS_PROGRAMUNIFORM 1
#include <string>

namespace Sce::Pss::Core::Graphics {
	typedef struct ProgramUniform {
		std::string Name;
		int Size;
		int Index;
		uint32_t Type;
		int Location;
		int Binding = -1;
	} ProgramUniform;
}

#endif