#include <Sce/Pss/Core/Graphics/CGX/Varying.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics::CGX::File;

namespace Sce::Pss::Core::Graphics::CGX {
	Varying::Varying(std::string name, std::string typeName, uint32_t size, uint32_t flags, ShaderGlobalType type)
		: super(name, typeName, size, flags)
	{
		Type = type;
		Logger::Debug("CGXVarying : type : " + Format::Hex(Type));
	}
	Varying::Varying(uint8_t * buf, CGXUniform* tblEntry)
		: super(buf, tblEntry)
	{
		Type = tblEntry->type;
		Logger::Debug("CGXVarying : type : " + Format::Hex(Type));
	}
}