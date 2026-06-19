#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobal.hpp>
#include <LibShared.hpp>

using namespace Sce::Pss::Core::Graphics::CGX::File;
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics::CGX {
	ShaderGlobal::ShaderGlobal(std::string name, std::string typeName)
	{
		Name = name;
		TypeName = typeName;
	}

	ShaderGlobal::ShaderGlobal(uint8_t * buf, CGXUniform * tblEntry)
	{
		if(tblEntry->namePtr != 0) Name = std::string(reinterpret_cast<char*>(buf + tblEntry->namePtr));
		if(tblEntry->typeNamePtr != 0) TypeName = std::string(reinterpret_cast<char*>(buf + tblEntry->typeNamePtr));

		Logger::Debug("CGXShaderGlobal : name : " + Name);
		Logger::Debug("CGXShaderGlobal : typename : " + TypeName);

	}
}