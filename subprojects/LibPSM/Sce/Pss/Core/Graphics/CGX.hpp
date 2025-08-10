#ifndef LIB_PSS_CGX_H
#define LIB_PSS_CGX_H 1
#include <string>
#include <cstdint>
#include <Sce/Pss/Core/Errorable.hpp>

#define CGX_MAX_LEN (0x10000)
#define CGX_MAGIC_LEN (0x4)

namespace Sce::Pss::Core::Graphics {


	enum class CGXVariantType : uint32_t {
		None = 0x0,
		Vertex = 0x1,
		Fragment = 0x2
	};

	typedef struct CGXVariantTableEntry {
		uint32_t nullSeperatorListPtr = 0;
		uint32_t VariantListPtr = 0;
		uint32_t VariantCount = 0;
		uint32_t unk0 = 0;
		uint32_t unk1 = 0;
		uint32_t unk2 = 0;
		CGXVariantType VariantType = CGXVariantType::None;
		uint32_t unk4 = 0;
	} CGXVariantTableEntry;

	typedef struct CGXVariant {
		char language[CGX_MAGIC_LEN] = { 0 };
		uint32_t sourcePtr = 0;
		uint32_t sourceSz = 0;
		uint32_t reserved = 0;
	} CGXVariant;

	typedef struct CGXHeader {
		char magic[CGX_MAGIC_LEN] = { 0 };
		char cgVer[CGX_MAGIC_LEN] = { 0 };
		char glesVer[CGX_MAGIC_LEN] = { 0 };
		uint32_t flags = 0;
		uint32_t unk0 = 0;
		uint32_t unk1 = 0;

		uint32_t vertexShaderVariantsPtr = 0;
		uint32_t unk2 = 0;
		uint32_t fragmentShaderVariantsPtr = 0;
		uint32_t unk4 = 0;

		uint32_t headerSize = 0;
		uint32_t shaderDataPtr = 0;
		uint32_t nullTermListStartPtr = 0;
		uint32_t nullTermListStartPtr2 = 0;
		uint32_t totalSize = 0;

		uint8_t hash[0x14] = { 0 };
	} CGXHeader;

	class CGX : public Errorable {
	private:
		uint8_t* cgxBuf = nullptr;
		size_t cgxSz = 0;

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