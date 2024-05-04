#ifndef LIB_PSS_CGX_H
#define LIB_PSS_CGX_H 1
#include <string>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
#define CGX_MAX_LEN (0x10000)
#define CGX_MAGIC_LEN (0x4)

	enum class CGXVariantType : uint32_t {
		Vertex = 0x1,
		Fragment = 0x2
	};

	typedef struct CGXVariantTableEntry {
		uint32_t nullSeperatorListPtr;
		uint32_t VariantListPtr;
		uint32_t VariantCount;
		int unk0;
		int unk1;
		int unk2;
		CGXVariantType VariantType;
		int unk4;
	} CGXVariantTableEntry;

	typedef struct CGXVariant {
		char language[CGX_MAGIC_LEN];
		uint32_t sourcePtr;
		uint32_t sourceSz;
		uint32_t reserved;
	} CGXVariant;

	typedef struct CGXHeader {
		char magic[CGX_MAGIC_LEN];
		char cgVer[CGX_MAGIC_LEN];
		char glesVer[CGX_MAGIC_LEN];
		uint32_t flags;
		int unk0;
		int unk1;

		uint32_t vertexShaderVariantsPtr;
		int unk2;
		uint32_t fragmentShaderVariantsPtr;
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
		CGXVariantTableEntry fragmentVariantTableEntry;
		CGXVariantTableEntry vertexVariantTableEntry;
		CGXVariant* fragmentVariants = nullptr;
		CGXVariant* vertexVariants = nullptr;

		bool headerIsValid();
	public:
		CGX(uint8_t* cgx, size_t cgxSz);
		~CGX();
		const std::string FindFragmentShader(const std::string& shaderLanguage);
		const std::string FindVertexShader(const std::string& shaderLanguage);
	};
}

#endif