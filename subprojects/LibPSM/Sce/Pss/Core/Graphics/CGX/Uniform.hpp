#ifndef LIB_PSS_CGX_UNIFORM_H
#define LIB_PSS_CGX_UNIFORM_H
#include <string>
#include <Sce/Pss/Core/Graphics/CGX/ShaderUniformType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobal.hpp>
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>

namespace Sce::Pss::Core::Graphics::CGX {
	class Uniform : public ShaderGlobal {
		typedef ShaderGlobal super;
	public:
		ShaderUniformType Type;

		Uniform(std::string name, std::string typeName, uint32_t size, uint32_t flags, ShaderUniformType type);
		Uniform(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXUniform* tblEntry);
	};

}

#endif