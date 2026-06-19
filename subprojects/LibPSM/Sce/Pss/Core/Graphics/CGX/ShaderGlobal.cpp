#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobal.hpp>
#include <LibShared.hpp>

using namespace Shared::String;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Graphics::CGX::File;

namespace Sce::Pss::Core::Graphics::CGX {
	ShaderGlobal::ShaderGlobal(std::string name, std::string typeName, uint32_t size, uint32_t flags)
	{
		Name = name;
		TypeName = typeName;
		Size = size;
		Flags = flags;

		Logger::Debug("CGXShaderGlobal : name : " + Name);
		Logger::Debug("CGXShaderGlobal : typename : " + TypeName);
		Logger::Debug("CGXShaderGlobal : size : " + Format::Hex(Size));
		Logger::Debug("CGXShaderGlobal : flags : " + Format::Hex(Flags));

	}

	ShaderGlobal::ShaderGlobal(uint8_t * buf, CGXUniform * tblEntry)
	{
		if(tblEntry->namePtr != 0) Name = std::string(reinterpret_cast<char*>(buf + tblEntry->namePtr));
		if(tblEntry->typeNamePtr != 0) TypeName = std::string(reinterpret_cast<char*>(buf + tblEntry->typeNamePtr));
		Size = tblEntry->size;
		Flags = tblEntry->flags;

		Logger::Debug("CGXShaderGlobal : name : " + Name);
		Logger::Debug("CGXShaderGlobal : typename : " + TypeName);
		Logger::Debug("CGXShaderGlobal : size : " + Format::Hex(Size));
		Logger::Debug("CGXShaderGlobal : flags : " + Format::Hex(Flags));


	}
}