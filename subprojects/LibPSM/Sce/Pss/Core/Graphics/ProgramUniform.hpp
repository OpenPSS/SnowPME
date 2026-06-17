#ifndef LIB_PSS_PROGRAMUNIFORM
#define LIB_PSS_PROGRAMUNIFORM 1
#include <Sce/Pss/Core/Graphics/ShaderUniformType.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>
#include <string>
#include <cstdint>

namespace Sce::Pss::Core::Graphics {
	typedef struct ProgramUniform {
		std::string Name;
		int Size;
		int Index;
		ShaderUniformType Type;
		int Location;
		int Binding = -1;
	} ProgramUniform;
}

#endif