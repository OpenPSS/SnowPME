#include <Sce/Pss/Core/Graphics/CGX/Attribute.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics::CGX::File;
namespace Sce::Pss::Core::Graphics::CGX {
	Attribute::Attribute(std::string name, std::string typeName, uint32_t size, uint32_t flags, ShaderAttributeType type)
		: super(name, typeName, size, flags)
	{
		Type = type;
		Logger::Debug("CGXAttribute : type : " + Format::Hex(static_cast<ShaderGlobalType>(Type)));
	}
	Attribute::Attribute(uint8_t* buf, CGXUniform* tblEntry)
		: super(buf, tblEntry)
	{
		Type = static_cast<ShaderAttributeType>(tblEntry->type);
		Logger::Debug("CGXAttribute : type : " + Format::Hex(static_cast<ShaderGlobalType>(Type)));
	}
}