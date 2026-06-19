#ifndef LIB_PSS_CGX_PARSER_H
#define LIB_PSS_CGX_PARSER_H 1

#include <string>
#include <cstdint>
#include <Sce/Pss/Core/Errorable.hpp>

#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderUniformType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderAttributeType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/VariantEntry.hpp>

#include <LibShared.hpp>
#include <memory>

namespace Sce::Pss::Core::Graphics::CGX {
	class CGXParser : public Errorable {
	private:
		std::vector<uint8_t> cgxFile;

		bool headerIsValid(Sce::Pss::Core::Graphics::CGX::File::CGXHeader* header);
	public:
		CGXParser(uint8_t* cgx, size_t cgxSz);
		~CGXParser() = default;
		
		std::unique_ptr<VariantEntry> VertexVariants = nullptr;
		std::unique_ptr<VariantEntry> FragmentVariants = nullptr;

		const std::string FindFragmentShader(const std::string& shaderLanguage);
		const std::string FindVertexShader(const std::string& shaderLanguage);
	};
}

#endif