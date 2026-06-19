#include <Sce/Pss/Core/Graphics/CGX/Variant.hpp>
#include <LibShared.hpp>
using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics::CGX::File;

namespace Sce::Pss::Core::Graphics::CGX {
	Variant::Variant(std::string shaderLang, std::string shader)
	{
		ShaderLanguage = shaderLang;
		Shader = shader;

		Logger::Debug("CGXVariant : lang : " + ShaderLanguage);
		Logger::Debug("CGXVariant : shader : " + Shader);
	}
	Variant::Variant(uint8_t* buf, CGXVariant* tblEntry)
	{
		ShaderLanguage = Format::Reverse(tblEntry->language, sizeof(CGXVariant::language));
		Shader = std::string(reinterpret_cast<char*>(buf + tblEntry->sourcePtr), tblEntry->sourceSz);

		Logger::Debug("CGXVariant : lang : " + ShaderLanguage);
		Logger::Debug("CGXVariant : shader : " + Shader);
	}
}
