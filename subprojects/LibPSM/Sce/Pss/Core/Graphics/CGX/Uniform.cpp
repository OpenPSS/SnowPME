#include <Sce/Pss/Core/Graphics/CGX/Uniform.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics::CGX::File;
namespace Sce::Pss::Core::Graphics::CGX {

	Uniform::Uniform(std::string name, std::string typeName, uint32_t size, uint32_t flags, ShaderUniformType type)
		: super(name, typeName, size, flags)
	{
		Type = static_cast<ShaderUniformType>(type);
		Logger::Debug("CGXUniform : type : " + Format::Hex(static_cast<ShaderGlobalType>(Type)));
	}

	Uniform::Uniform(uint8_t* buf, CGXUniform* tblEntry)
		: super(buf, tblEntry)
	{
		Type = static_cast<ShaderUniformType>(tblEntry->type);
		Logger::Debug("CGXUniform : type : " + Format::Hex(static_cast<ShaderGlobalType>(Type)));
	}

}