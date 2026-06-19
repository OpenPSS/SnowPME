#include <Sce/Pss/Core/Graphics/CGX/CGXParser.hpp>
#include <Sce/Pss/Core/Graphics/CGX/CGXFile.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Graphics::CGX::File;

namespace Sce::Pss::Core::Graphics::CGX {
	bool CGXParser::headerIsValid(CGXHeader* header) {
		if (header == nullptr)
			return true;

		if (header->headerSize < offsetof(CGXHeader, hash))
			return false;

		if (header->shaderDataPtr < header->headerSize)
			return false;

		if (header->stringTblPtr < header->shaderDataPtr)
			return false;

		if (header->stringTblPtr2 < header->stringTblPtr)
			return false;

		if (header->totalSize < header->stringTblPtr2 || this->cgxFile.size() < header->totalSize)
			return false;

		if (header->unk1 > 0x400)
			return false;

		if (header->unk2 > 0x400)
			return false;

		if (header->unk4 > 0x400)
			return false;

		if ((header->unk0 & 3) != 0)
			return false;

		if (header->unk0 != 0)
		{
			if (header->unk0 < header->headerSize || header->unk0 + 16 * header->unk1 > header->shaderDataPtr)
				return false;
		}
		else if (header->unk1) {
			return false;
		}

		// TODO: implement the rest of the checks
		return true;
	}

	CGXParser::CGXParser(uint8_t* cgx, size_t cgxSz) {
		if (cgx == nullptr) {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
			return;
		}
		if (cgxSz < sizeof(CGXHeader) ||
			cgxSz > CGX_MAX_LEN) {

			ExceptionInfo::AddMessage("Unsupported shader file\n");
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
			return;
		}

		this->cgxFile.resize(cgxSz);
		memcpy(this->cgxFile.data(), cgx, cgxSz);

		CGXHeader* header = reinterpret_cast<CGXHeader*>(this->cgxFile.data());

		std::string magic = Format::Reverse(header->magic, sizeof(CGXHeader::magic));
		std::string cgVer = Format::Reverse(header->cgVer, sizeof(CGXHeader::cgVer));
		std::string glesVer = Format::Reverse(header->glesVer, sizeof(CGXHeader::glesVer));
		Logger::Debug("CGX : "+magic+" "+cgVer+" "+glesVer);

		bool isValid = magic == CGX_MAGIC && cgVer == CG_VER && glesVer == GLES_VER;

		if (!isValid || !this->headerIsValid(header)) {
			ExceptionInfo::AddMessage("Corrupted shader file\n");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		if (header->vertexShaderVariantsPtr != 0) {
			CGXVariantTableEntry* tblEntry = reinterpret_cast<CGXVariantTableEntry*>(cgxFile.data() + header->vertexShaderVariantsPtr);
			this->VertexVariants = std::make_unique<VariantEntry>(cgxFile.data(), tblEntry);
		}

		if (header->fragmentShaderVariantsPtr != 0) {
			CGXVariantTableEntry* tblEntry = reinterpret_cast<CGXVariantTableEntry*>(cgxFile.data() + header->fragmentShaderVariantsPtr);
			this->FragmentVariants = std::make_unique<VariantEntry>(cgxFile.data(), tblEntry);
		}

	}
	const std::string CGXParser::FindVertexShader(const std::string& shaderLanguage) {
		for(const auto& variant : this->VertexVariants->Variants) {
			if(variant.ShaderLanguage == shaderLanguage) {
				return variant.Shader;
			}
		}
		ExceptionInfo::AddMessage("Vertex shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}

	const std::string CGXParser::FindFragmentShader(const std::string& shaderLanguage) {
		for (const auto& variant : this->FragmentVariants->Variants) {
			if (variant.ShaderLanguage == shaderLanguage) {
				return variant.Shader;
			}
		}
		ExceptionInfo::AddMessage("Fragment shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}
}
