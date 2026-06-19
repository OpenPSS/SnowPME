#ifndef LIB_PSS_CGX_ATTRIBUTE_H
#define LIB_PSS_CGX_ATTRIBUTE_H
#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobal.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderAttributeType.hpp>

namespace Sce::Pss::Core::Graphics::CGX {
	class Attribute : public ShaderGlobal {
		typedef ShaderGlobal super;
	public:
		ShaderAttributeType Type;
		Attribute(std::string name, std::string typeName, ShaderAttributeType type);
		Attribute(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXUniform* tblEntry);
	};
}


#endif