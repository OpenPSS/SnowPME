#ifndef LIB_PSM_CGX_H
#define LIB_PSM_CGX_H 1
#include <string>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
#define CGX_MAX_LEN (0x10000)
#define CGX_MAGIC_LEN (0x4)

	typedef struct CGXVarientTableEntry {
		uint32_t nullSeperatorListPtr;
		uint32_t varientListPtr;
		uint32_t varientCount;
		char unk0[0x14];
	} CGXVarientTableEntry;

	typedef struct CGXVarient {
		char language[CGX_MAGIC_LEN];
		uint32_t sourcePtr;
		uint32_t sourceSz;
		uint32_t reserved;
	} CGXVarient;

	typedef struct CGXHeader {
		char magic[CGX_MAGIC_LEN];
		char cgVer[CGX_MAGIC_LEN];
		char glesVer[CGX_MAGIC_LEN];
		uint32_t flags;
		char unk0[8];
		uint32_t varientTablePtr;
		char unk1[0x24];
		//char hash[0x10];
	} CGXHeader;

	class CGX : public Errorable{
	private:
		std::byte* cgxBuf;
		size_t cgxSz;

		std::string magic;
		std::string cgVer;
		std::string glesVer;

		CGXHeader header;
		CGXVarientTableEntry fragmentVarientTableEntry;
		CGXVarientTableEntry vertexVarientTableEntry;
		CGXVarient* fragmentVarients;
		CGXVarient* vertexVarients;
	public:
		CGX(std::byte* cgx, size_t cgxSz);
		~CGX();
		std::string FragmentShader(std::string shaderLanguage);
		std::string VertexShader(std::string shaderLanguage);
	};
}

#endif