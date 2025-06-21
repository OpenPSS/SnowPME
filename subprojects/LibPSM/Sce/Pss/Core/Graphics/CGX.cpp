#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>
#include <cstring>
#include <iostream>
#include <algorithm>

namespace Sce::Pss::Core::Graphics {
	using namespace Shared::Debug;

	inline std::string reversed(char* data, size_t len) {
		std::string out(data, data + len);
		std::reverse(out.begin(), out.end());
		return out;
	}

	bool CGX::headerIsValid() {
		if (this->cgxBuf == nullptr) 
			return true;

		if (this->header.headerSize < 0x40)
			return false;

		if (this->header.shaderDataPtr < this->header.headerSize)
			return false;
		
		if (this->header.nullTermListStartPtr < this->header.shaderDataPtr)
			return false;
		
		if (this->header.nullTermListStartPtr2 < this->header.nullTermListStartPtr)
			return false;

		if (this->header.totalSize < this->header.nullTermListStartPtr2 || this->cgxSz < this->header.totalSize)
			return false;
		
		if (this->header.unk1 > 0x400)
			return false;
		
		if (this->header.unk2 > 0x400)
			return false;

		if (this->header.unk4 > 0x400)
			return false;

		if ((this->header.unk0 & 3) != 0)
			return false;

		if (this->header.unk0)
		{
			if (this->header.unk0 < this->header.headerSize || this->header.unk0 + 16 * this->header.unk1 > this->header.shaderDataPtr)
				return false;
		}
		else if (this->header.unk1) {
			return false;
		}

		// TODO: implement the rest of the checks
		return true;
	}

	CGX::CGX(uint8_t* cgx, size_t cgxSz) {
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

		this->cgxBuf = cgx;
		this->cgxSz = cgxSz;
		this->header = *(CGXHeader*)this->cgxBuf;

		std::string magic = reversed(this->header.magic, 4);
		std::string cgVer = reversed(this->header.cgVer, 4);
		std::string glesVer = reversed(this->header.glesVer, 4);
		Logger::Debug("CGX: "+magic+" "+cgVer+" "+glesVer);

		bool is_valid = magic == ".CGX" && cgVer == "0.95" && glesVer == "ES20";
		if (!is_valid || !this->headerIsValid()) {
			ExceptionInfo::AddMessage("Corrupted shader file\n");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		this->fragmentVariantTableEntry = {0};
		this->vertexVariantTableEntry = {0};

		if (this->header.vertexShaderVariantsPtr != 0) {
			this->vertexVariantTableEntry = *(CGXVariantTableEntry*)(this->cgxBuf + this->header.vertexShaderVariantsPtr);
			this->vertexVariants.reserve(this->vertexVariantTableEntry.VariantCount);

			for (uint32_t i = 0; i < this->vertexVariantTableEntry.VariantCount; i++) {
				CGXVariant variant = ((CGXVariant*)(this->cgxBuf + this->vertexVariantTableEntry.VariantListPtr))[i];
				this->vertexVariants.push_back(variant);
				std::string language = reversed(variant.language, 4);
				Logger::Debug("CGX : vert : lang : " + language);
			}
		}

		if (this->header.fragmentShaderVariantsPtr != 0) {
			this->fragmentVariantTableEntry = *(CGXVariantTableEntry*)(this->cgxBuf + this->header.fragmentShaderVariantsPtr);
			this->fragmentVariants.reserve(this->fragmentVariantTableEntry.VariantCount);

			for (uint32_t i = 0; i < this->fragmentVariantTableEntry.VariantCount; i++) {
				CGXVariant variant = ((CGXVariant*)(this->cgxBuf + this->fragmentVariantTableEntry.VariantListPtr))[i];
				this->fragmentVariants.push_back(variant);
				std::string language = reversed(variant.language, 4);
				Logger::Debug("CGX : frag : lang : " + language);
			}
		}
	}
	const std::string CGX::FindVertexShader(const std::string& shaderLanguage) {
		for(CGXVariant& variant : this->vertexVariants) {
			if(reversed(variant.language, 4) == shaderLanguage) {
				const char* shaderData = (char*)(this->cgxBuf + variant.sourcePtr);
					return std::string(shaderData, variant.sourceSz);
			}
		}
		ExceptionInfo::AddMessage("Vertex shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}

	const std::string CGX::FindFragmentShader(const std::string& shaderLanguage) {
		for(CGXVariant& variant : this->fragmentVariants) {
			if(reversed(variant.language, 4) == shaderLanguage) {
				const char* shaderData = (char*)(this->cgxBuf + variant.sourcePtr);
					return std::string(shaderData, variant.sourceSz);
			}
		}
		ExceptionInfo::AddMessage("Fragment shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}

	CGX::~CGX() {}
}
