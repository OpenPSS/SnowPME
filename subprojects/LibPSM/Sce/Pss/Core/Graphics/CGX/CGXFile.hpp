#ifndef LIB_PSS_CGX_FILE_H
#define LIB_PSS_CGX_FILE_H

#include <Sce/Pss/Core/Graphics/CGX/ShaderGlobalType.hpp>
#include <LibShared.hpp>

#include <cstdint>
#include <cstdio>
#include <cstddef>

namespace Sce::Pss::Core::Graphics::CGX::File {

	#define CGX_MAX_LEN (0x10000)
	#define CGX_MAGIC_LEN (0x04)

	#define CGX_MAGIC (".CGX")
	#define CG_VER ("0.95")
	#define GLES_VER ("ES20")

	enum class CGXVariantType : uint32_t {
		None = 0,
		Vertex = 1,
		Fragment = 2
	};

	typedef PACK(struct CGXUniform {
		uint32_t namePtr;
		uint32_t typeNamePtr;
		uint32_t unk1;
		ShaderGlobalType type;
		uint32_t size;
		uint32_t flags;
	}) CGXUniform;

	typedef PACK(struct CGXVariant {
		char language[CGX_MAGIC_LEN];
		uint32_t sourcePtr;
		uint32_t sourceSz;
		uint32_t reserved;
	}) CGXVariant;

	typedef PACK(struct CGXVariantTableEntry {
		uint32_t namePtr;
		
		uint32_t variantListPtr;
		uint32_t variantsNum;

		uint32_t uniformsPtr;
		uint32_t uniformsNum;
		uint32_t attributesNum;
		uint32_t varyingsNum;
		
		uint32_t unk4;
	}) CGXVariantTableEntry;

	typedef PACK(struct CGXHeader {
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
		uint32_t stringTblPtr;
		uint32_t stringTblPtr2;
		uint32_t totalSize;

		uint8_t hash[0x14];
	}) CGXHeader;
}

#endif