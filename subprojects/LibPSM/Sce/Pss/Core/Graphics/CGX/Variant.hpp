#ifndef LIB_PSS_CGX_VARIENT_H
#define LIB_PSS_CGX_VARIENT_H
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <string>

namespace Sce::Pss::Core::Graphics::CGX {
	class Variant {
	public:
		std::string ShaderLanguage;
		std::string Shader;

		Variant(std::string shaderLang, std::string shader);
		Variant(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXVariant* tblEntry);
	};
}

#endif