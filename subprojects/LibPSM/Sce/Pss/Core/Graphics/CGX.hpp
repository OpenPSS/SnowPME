#ifndef LIB_PSS_CGX_H
#define LIB_PSS_CGX_H 1
#include <string>
#include <cstdint>
#include <Sce/Pss/Core/Errorable.hpp>

#define CGX_MAX_LEN (0x10000)
#define CGX_MAGIC_LEN (0x4)

namespace Sce::Pss::Core::Graphics {


	enum class CGXVariantType : uint32_t {
		Vertex = 0x1,
		Fragment = 0x2
	};

	typedef struct CGXVariantTableEntry {
		uint32_t nullSeperatorListPtr;
		uint32_t VariantListPtr;
		uint32_t VariantCount;
		uint32_t unk0;
		uint32_t unk1;
		uint32_t unk2;
		CGXVariantType VariantType;
		uint32_t unk4;
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
		uint32_t unk0;
		uint32_t unk1;

		uint32_t vertexShaderVariantsPtr;
		uint32_t unk2;
		uint32_t fragmentShaderVariantsPtr;
		uint32_t unk4;

		uint32_t headerSize;
		uint32_t shaderDataPtr;
		uint32_t nullTermListStartPtr;
		uint32_t nullTermListStartPtr2;
		uint32_t totalSize;

		uint8_t hash[0x14];
	} CGXHeader;

	class CGX : public Errorable {
	private:
		uint8_t* cgxBuf;
		size_t cgxSz;

		CGXHeader header;
		CGXVariantTableEntry fragmentVariantTableEntry;
		CGXVariantTableEntry vertexVariantTableEntry;
		std::vector<CGXVariant> fragmentVariants;
		std::vector<CGXVariant> vertexVariants;

		bool headerIsValid();
	public:
		CGX(uint8_t* cgx, size_t cgxSz);
		~CGX();
		const std::string FindFragmentShader(const std::string& shaderLanguage);
		const std::string FindVertexShader(const std::string& shaderLanguage);
	};
}

#endif