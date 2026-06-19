#ifndef LIB_PSS_CGX_SUPER_GLOBAL_H
#define LIB_PSS_CGX_SUPER_GLOBAL_H
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <string>

namespace Sce::Pss::Core::Graphics::CGX {
	class ShaderGlobal {
	public:
		std::string Name;
		std::string TypeName;

		ShaderGlobal(std::string name, std::string typeName);
		ShaderGlobal(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXUniform* tblEntry);
	};
}

#endif