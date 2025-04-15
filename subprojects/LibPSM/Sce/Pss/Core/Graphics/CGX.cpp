#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>
#include <cstring>

namespace Sce::Pss::Core::Graphics {
	using namespace Shared::Debug;



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

		this->magic = Shared::String::StringUtil::Reverse(std::string(this->header.magic, CGX_MAGIC_LEN));
		this->cgVer = Shared::String::StringUtil::Reverse(std::string(this->header.cgVer, CGX_MAGIC_LEN));
		this->glesVer = Shared::String::StringUtil::Reverse(std::string(this->header.glesVer, CGX_MAGIC_LEN));

		Logger::Debug("CGX : " + this->magic + " " + this->cgVer + " "+ this->glesVer);

		if (!(this->magic == ".CGX" &&
			this->cgVer == "0.95" &&
			this->glesVer == "ES20")) {

			ExceptionInfo::AddMessage("Unsupported shader file\n");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		if (!this->headerIsValid()) {
			ExceptionInfo::AddMessage("Corrupted shader file\n");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		memset((void*)&this->fragmentVariantTableEntry, 0, sizeof(this->fragmentVariantTableEntry));
		memset((void*)&this->vertexVariantTableEntry, 0, sizeof(this->fragmentVariantTableEntry));

		if (this->header.vertexShaderVariantsPtr != 0) {
			memcpy(&this->vertexVariantTableEntry, (CGXVariantTableEntry*)(this->cgxBuf + this->header.vertexShaderVariantsPtr), sizeof(CGXVariantTableEntry));
		
			this->vertexVariants = new CGXVariant[this->vertexVariantTableEntry.VariantCount];

			for (uint32_t i = 0; i < this->vertexVariantTableEntry.VariantCount; i++) {
				this->vertexVariants[i] = ((CGXVariant*)(this->cgxBuf + this->vertexVariantTableEntry.VariantListPtr))[i];

				Logger::Debug("CGX : vert : lang : " + Shared::String::StringUtil::Reverse(std::string(this->vertexVariants[i].language, CGX_MAGIC_LEN)));
			}
		}

		if (this->header.fragmentShaderVariantsPtr != 0) {
			memcpy(&this->fragmentVariantTableEntry, (CGXVariantTableEntry*)(this->cgxBuf + this->header.fragmentShaderVariantsPtr), sizeof(CGXVariantTableEntry));


			this->fragmentVariants = new CGXVariant[this->fragmentVariantTableEntry.VariantCount];

			for (uint32_t i = 0; i < this->fragmentVariantTableEntry.VariantCount; i++) {
				this->fragmentVariants[i] = ((CGXVariant*)(this->cgxBuf + this->fragmentVariantTableEntry.VariantListPtr))[i];

				Logger::Debug("CGX : frag : lang : " + Shared::String::StringUtil::Reverse(std::string(this->fragmentVariants[i].language, CGX_MAGIC_LEN)));
			}
		}
	}
	const std::string CGX::FindVertexShader(const std::string& shaderLanguage) {
		if (this->vertexVariants != NULL) {
			
			for (uint32_t i = 0; i < this->vertexVariantTableEntry.VariantCount; i++) {
				std::string foundLanguage = Shared::String::StringUtil::Reverse(std::string(this->vertexVariants[i].language, CGX_MAGIC_LEN));

				if (foundLanguage == shaderLanguage) {
					const char* shaderData = (char*)(this->cgxBuf + this->vertexVariants[i].sourcePtr);
					return std::string(shaderData, this->vertexVariants[i].sourceSz);
				}
			}

		}
		ExceptionInfo::AddMessage("Vertex shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}

	const std::string CGX::FindFragmentShader(const std::string& shaderLanguage) {
		if (this->fragmentVariants != NULL) {
			for (uint32_t i = 0; i < this->fragmentVariantTableEntry.VariantCount; i++) {
				std::string foundLanguage = Shared::String::StringUtil::Reverse(std::string(this->fragmentVariants[i].language, CGX_MAGIC_LEN));

				if (foundLanguage == shaderLanguage) {
					const char* shaderData = (char*)(this->cgxBuf + this->fragmentVariants[i].sourcePtr);
					return std::string(shaderData, this->fragmentVariants[i].sourceSz);
				}
			}
		}

		ExceptionInfo::AddMessage("Fragment shader not found\n");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return "";
	}

	CGX::~CGX() {		
		delete[] fragmentVariants;
		delete[] vertexVariants;
	}


}