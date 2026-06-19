#ifndef LIB_PSS_CGX_VARIENT_ENTRY_H
#define LIB_PSS_CGX_VARIENT_ENTRY_H
#include <Sce/Pss/Core/Graphics/CGX/Variant.hpp>
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <Sce/Pss/Core/Graphics/CGX/Uniform.hpp>
#include <Sce/Pss/Core/Graphics/CGX/Attribute.hpp>
#include <Sce/Pss/Core/Graphics/CGX/Varying.hpp>
#include <cstdint>
#include <vector>

namespace Sce::Pss::Core::Graphics::CGX {
	class VariantEntry {
	public:
		std::string Name;
		std::vector<Variant> Variants;
		std::vector<Uniform> Uniforms;
		std::vector<Attribute> Attributes;
		std::vector<Varying> Varyings;

		VariantEntry(uint8_t* buf, Sce::Pss::Core::Graphics::CGX::File::CGXVariantTableEntry* tblEntry);

	};
}

#endif