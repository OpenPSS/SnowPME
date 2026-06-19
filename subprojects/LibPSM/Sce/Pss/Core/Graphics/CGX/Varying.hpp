#ifndef LIB_PSS_CGX_VARYING_H
#define LIB_PSS_CGX_VARYING_H
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobalType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobal.hpp>

namespace Sce::Pss::Core::Graphics::CGX {
	class Varying : public ShaderGlobal {
		typedef ShaderGlobal super;
	public:
		ShaderGlobalType Type;

		Varying(std::string name, std::string typeName, ShaderGlobalType type);
		Varying(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXUniform* tblEntry);
	};
}


#endif