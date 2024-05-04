#ifndef LIB_PSS_CGX_H
#define LIB_PSS_CGX_H 1
#include <string>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
#define CGX_MAX_LEN (0x10000)
#define CGX_MAGIC_LEN (0x4)

	enum class CGXVarientType : uint32_t {
		Vertex = 0x1,
		Fragment = 0x2
	};

	typedef struct CGXVarientTableEntry {
		uint32_t nullSeperatorListPtr;
		uint32_t varientListPtr;
		uint32_t varientCount;
		int unk0;
		int unk1;
		int unk2;
		CGXVarientType varientType;
		int unk4;
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
		int unk0;
		int unk1;

		uint32_t vertexShaderVarientsPtr;
		int unk2;
		uint32_t fragmentShaderVarientsPtr;
		int unk4;

		uint32_t headerSize;
		uint32_t shaderDataPtr;
		uint32_t nullTermListStartPtr;
		uint32_t nullTermListStartPtr2;
		uint32_t totalSize;

		uint8_t hash[0x14];
	} CGXHeader;

	class CGX : public Errorable{
	private:
		uint8_t* cgxBuf;
		size_t cgxSz;

		std::string magic;
		std::string cgVer;
		std::string glesVer;

		CGXHeader header;
		CGXVarientTableEntry fragmentVarientTableEntry;
		CGXVarientTableEntry vertexVarientTableEntry;
		CGXVarient* fragmentVarients = nullptr;
		CGXVarient* vertexVarients = nullptr;

		bool headerIsValid();
	public:
		CGX(uint8_t* cgx, size_t cgxSz);
		~CGX();
		std::string FragmentShader(std::string shaderLanguage);
		std::string VertexShader(std::string shaderLanguage);
	};
}

#endif