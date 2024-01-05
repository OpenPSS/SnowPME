#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Graphics {

	bool CGX::headerIsValid() {
		if (this->cgxBuf == nullptr) {
			return true;
		}
		if (this->header.headerSize < 64)
			return false;

		if (this->header.unk5 < this->header.headerSize)
			return false;
		
		if (this->header.unk6 < this->header.unk5)
			return false;
		
		if (this->header.unk7 < this->header.unk6)
			return false;

		if (this->header.totalSize < this->header.unk7 || this->cgxSz < this->header.totalSize)
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
			if (this->header.unk0 < this->header.headerSize || this->header.unk0 + 16 * this->header.unk1 > this->header.unk5)
				return false;
		}
		else if (this->header.unk1)
		{
			return false;
		}

		// TODO: implement the rest of the checks
	}

	CGX::CGX(uint8_t* cgx, size_t cgxSz) {
		
		if (cgx == nullptr) {
			this->SetError(PSM_ERROR_COMMON_ARGUMENT_NULL);
			return;
		}
		if (cgxSz < sizeof(CGXHeader) ||
			cgxSz > CGX_MAX_LEN) {

			ExceptionInfo::AddMessage("Unsupported shader file");
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

			ExceptionInfo::AddMessage("Unsupported shader file");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		if (!this->headerIsValid()) {
			ExceptionInfo::AddMessage("Corrupted shader file");
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
			return;
		}

		CGXVarientTableEntry* varientTable = (CGXVarientTableEntry*)(this->cgxBuf + this->header.varientTablePtr);

		this->vertexVarientTableEntry = varientTable[0];
		this->fragmentVarientTableEntry = varientTable[1];

		this->fragmentVarients = new CGXVarient[this->fragmentVarientTableEntry.varientCount];
		this->vertexVarients = new CGXVarient[this->vertexVarientTableEntry.varientCount];

		for (uint32_t i = 0; i < this->fragmentVarientTableEntry.varientCount; i++) {
			this->fragmentVarients[i] = ((CGXVarient*)(this->cgxBuf + this->fragmentVarientTableEntry.varientListPtr))[i];

			Logger::Debug("CGX : frag : lang : " + Shared::String::StringUtil::Reverse(std::string(this->fragmentVarients[i].language, CGX_MAGIC_LEN)));
		}

		for (uint32_t i = 0; i < this->vertexVarientTableEntry.varientCount; i++) {
			this->vertexVarients[i] = ((CGXVarient*)(this->cgxBuf + this->vertexVarientTableEntry.varientListPtr))[i];

			Logger::Debug("CGX : vert : lang : " + Shared::String::StringUtil::Reverse(std::string(this->vertexVarients[i].language, CGX_MAGIC_LEN)));
		}

	}
	std::string CGX::VertexShader(std::string shaderLanguage) {
		for (uint32_t i = 0; i < this->vertexVarientTableEntry.varientCount; i++) {
			std::string foundLanguage = Shared::String::StringUtil::Reverse(std::string(this->vertexVarients[i].language, CGX_MAGIC_LEN));

			if (foundLanguage == shaderLanguage) {
				return std::string((char*)(this->cgxBuf + this->vertexVarients[i].sourcePtr), this->vertexVarients[i].sourceSz);
			}
		}
		ExceptionInfo::AddMessage("Vertex shader not found");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return std::string();
	}

	std::string CGX::FragmentShader(std::string shaderLanguage) {
		for (uint32_t i = 0; i < this->fragmentVarientTableEntry.varientCount; i++) {
			std::string foundLanguage = Shared::String::StringUtil::Reverse(std::string(this->fragmentVarients[i].language, CGX_MAGIC_LEN));

			if (foundLanguage == shaderLanguage) {
				return std::string((char*)(this->cgxBuf + this->fragmentVarients[i].sourcePtr), this->fragmentVarients[i].sourceSz);
			}
		}

		ExceptionInfo::AddMessage("Fragment shader not found");
		this->SetError(PSM_ERROR_COMMON_FILE_LOAD);
		return std::string();
	}

	CGX::~CGX() {		
		delete[] fragmentVarients;
		delete[] vertexVarients;
	}


}