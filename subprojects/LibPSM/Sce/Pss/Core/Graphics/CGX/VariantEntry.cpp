#include <Sce/Pss/Core/Graphics/CGX/VariantEntry.hpp>
#include <Sce/Pss/Core/Graphics/CGX/Variant.hpp>
#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;

using namespace Sce::Pss::Core::Graphics::CGX::File;

namespace Sce::Pss::Core::Graphics::CGX {
	VariantEntry::VariantEntry(uint8_t* buf, CGXVariantTableEntry* tblEntry)
	{
		if(tblEntry->namePtr != 0) Name = std::string(reinterpret_cast<char*>(buf + tblEntry->namePtr));
		
		Logger::Debug("CGXVariantEntry : name : " + Name);

		CGXVariant* variants = reinterpret_cast<CGXVariant*>(buf + tblEntry->variantListPtr);
		CGXUniform* uniforms = reinterpret_cast<CGXUniform*>(buf + tblEntry->uniformsPtr);
		CGXUniform* attributes = &uniforms[tblEntry->uniformsNum];
		CGXUniform* varyings = &attributes[tblEntry->attributesNum];

		

		for (uint32_t i = 0; i < tblEntry->variantsNum; i++) {
			this->Variants.emplace_back(buf, &variants[i]);
		}

		for (uint32_t i = 0; i < tblEntry->uniformsNum; i++) {
			this->Uniforms.emplace_back(buf, &uniforms[i]);
		}

		for (uint32_t i = 0; i < tblEntry->attributesNum; i++) {
			this->Attributes.emplace_back(buf, &attributes[i]);
		}

		for (uint32_t i = 0; i < tblEntry->varyingsNum; i++) {
			this->Varyings.emplace_back(buf, &varyings[i]);
		}

	}
}