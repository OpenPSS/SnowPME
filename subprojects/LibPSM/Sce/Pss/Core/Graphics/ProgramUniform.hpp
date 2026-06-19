#ifndef LIB_PSS_PROGRAMUNIFORM
#define LIB_PSS_PROGRAMUNIFORM 1
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobalType.hpp>
#include <Sce/Pss/Core/Graphics/GraphicsExtension.hpp>
#include <string>
#include <cstdint>

namespace Sce::Pss::Core::Graphics {
	typedef struct ProgramUniform {
		std::string Name;
		int Size = 0;
		int ESize = 0;
		int Flags = 0;
		int Index = 0;
		Sce::Pss::Core::Graphics::CGX::ShaderUniformType Type = Sce::Pss::Core::Graphics::CGX::ShaderUniformType::None;
		int Location = -1;
		int Binding = -1;
		int Stream = 0;
		int Texture = -1;
	} ProgramUniform;
}

#endif