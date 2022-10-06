#include <Graphics/CGX.hpp>
#include <Debug/Logger.hpp>
#include <mono/mono.h>
#include <LibPSM.hpp>
using namespace SnowPME::Debug;

namespace SnowPME::Graphics {

	CGX::CGX(std::byte* cgx, size_t cgxSz) {
		
		if (cgx == NULL) {
			Logger::Error("CGX was null");
			AppGlobals::SetPsmLastError(PSM_ERROR_COMMON_ARGUMENT_NULL);
			throw new std::exception("CGX was null");
		}
		if (cgxSz < sizeof(CGXHeader) ||
			cgxSz > CGX_MAX_LEN) {

			Logger::Error("Unsupported shader file");
			AppGlobals::SetPsmLastError(PSM_ERROR_COMMON_FILE_LOAD);
			throw new std::exception("Unsupported shader file");
		}


		this->cgxBuf = cgx;
		this->cgxSz = cgxSz;

		this->header = *(CGXHeader*)this->cgxBuf;

		this->magic = StringUtils::Reverse(std::string(this->header.magic, CGX_MAGIC_LEN));
		this->cgVer = StringUtils::Reverse(std::string(this->header.cgVer, CGX_MAGIC_LEN));
		this->glesVer = StringUtils::Reverse(std::string(this->header.glesVer, CGX_MAGIC_LEN));

		Logger::Debug("CGX : " + this->magic + " " + this->cgVer + " "+ this->glesVer);

		if (!(this->magic == ".CGX" &&
			this->cgVer == "0.95" &&
			this->glesVer == "ES20")) {

			Logger::Error("Unsupported shader file");
			AppGlobals::SetPsmLastError(PSM_ERROR_COMMON_FILE_LOAD);
			throw new std::exception("Unsupported shader file");
		}
		CGXVarientTableEntry* varientTable = (CGXVarientTableEntry*)(this->cgxBuf + this->header.varientTablePtr);

		this->vertexVarientTableEntry = varientTable[0];
		this->fragmentVarientTableEntry = varientTable[1];

		this->fragmentVarients = new CGXVarient[this->fragmentVarientTableEntry.varientCount];
		this->vertexVarients = new CGXVarient[this->vertexVarientTableEntry.varientCount];

		for (uint32_t i = 0; i < this->fragmentVarientTableEntry.varientCount; i++) {
			this->fragmentVarients[i] = ((CGXVarient*)(this->cgxBuf + this->fragmentVarientTableEntry.varientListPtr))[i];

			Logger::Debug("CGX : frag : lang : " + StringUtils::Reverse(std::string(this->fragmentVarients[i].language, CGX_MAGIC_LEN)));
		}

		for (uint32_t i = 0; i < this->vertexVarientTableEntry.varientCount; i++) {
			this->vertexVarients[i] = ((CGXVarient*)(this->cgxBuf + this->vertexVarientTableEntry.varientListPtr))[i];

			Logger::Debug("CGX : vert : lang : " + StringUtils::Reverse(std::string(this->vertexVarients[i].language, CGX_MAGIC_LEN)));
		}

	}
	std::string CGX::VertexShader(std::string shaderLanguage) {
		for (uint32_t i = 0; i < this->vertexVarientTableEntry.varientCount; i++) {
			std::string foundLanguage = StringUtils::Reverse(std::string(this->vertexVarients[i].language, CGX_MAGIC_LEN));

			if (foundLanguage == shaderLanguage) {
				return std::string((char*)(this->cgxBuf + this->vertexVarients[i].sourcePtr), this->vertexVarients[i].sourceSz);
			}
		}

		AppGlobals::SetPsmLastError(PSM_ERROR_COMMON_FILE_LOAD);
		Logger::Error("Vertex shader not found");
		throw new std::exception("Vertex shader not found");
	}

	std::string CGX::FragmentShader(std::string shaderLanguage) {
		for (uint32_t i = 0; i < this->fragmentVarientTableEntry.varientCount; i++) {
			std::string foundLanguage = StringUtils::Reverse(std::string(this->fragmentVarients[i].language, CGX_MAGIC_LEN));

			if (foundLanguage == shaderLanguage) {
				return std::string((char*)(this->cgxBuf + this->fragmentVarients[i].sourcePtr), this->fragmentVarients[i].sourceSz);
			}
		}

		AppGlobals::SetPsmLastError(PSM_ERROR_COMMON_FILE_LOAD);
		Logger::Error("Fragment shader not found");
		throw new std::exception("Fragment shader not found");
	}

	CGX::~CGX() {		
		delete[] fragmentVarients;
		delete[] vertexVarients;
	}


}