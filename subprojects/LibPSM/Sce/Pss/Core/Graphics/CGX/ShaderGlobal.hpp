#ifndef LIB_PSS_CGX_SUPER_GLOBAL_H
#define LIB_PSS_CGX_SUPER_GLOBAL_H
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <string>

namespace Sce::Pss::Core::Graphics::CGX {
	class ShaderGlobal {
	public:
		std::string Name = "";
		std::string TypeName = "";
		uint32_t Size = 0;
		uint32_t Flags = 0;

		ShaderGlobal(std::string name, std::string typeName, uint32_t size, uint32_t flags);
		ShaderGlobal(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXUniform* tblEntry);
	};
}

#endif