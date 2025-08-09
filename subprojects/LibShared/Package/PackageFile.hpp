/*
* PKG extraction code based on
* Real-PackageExtractor-Installer by LiEnby.
* https://silica.codes/Li/real-PackageExtractor-installer/
*/

#ifndef SHARED_PACKAGE_FILE_H 
#define SHARED_PACKAGE_FILE_H 1

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <CompilerCompat.hpp>

#define SCE_NPDRM_PACKAGE_CHECK_SIZE (0x8000)

#define IS_PS3_KEY(x) ( ((x >> 0x1C)&7) == PKG_KEYID_PS3)
#define IS_PSP_CONTENT_TYPE(x) (x == PKG_TYPE_PSX || x == PKG_TYPE_PSP || x == PKG_TYPE_PSP_GO || x == PKG_TYPE_PSP_MINIS || x == PKG_TYPE_PSP_NEO_GEO)
#define IS_PSM_CONTENT_TYPE(x) (x == PKG_TYPE_PSM || x == PKG_TYPE_PSM_UNITY)

PACK(typedef struct PKG_ITEM_RECORD {
	uint32_t filename_offset = 0;
	uint32_t filename_size = 0;
	uint64_t data_offset = 0;
	uint64_t data_size = 0;
	uint32_t flags = 0;
	uint32_t reserved = 0;
}) PKG_ITEM_RECORD;

PACK(typedef struct PKG_FILE_HEADER {
	char magic[4] = { 0 };
	uint16_t revision = 0;
	uint16_t type = 0;
	uint32_t meta_offset = 0;
	uint32_t meta_count = 0;
	uint32_t meta_size = 0;
	uint32_t item_count = 0;
	uint64_t total_size = 0;
	uint64_t data_offset = 0;
	uint64_t data_size = 0;
	char content_id[0x30] = { 0 };
	uint8_t digest[0x10] = { 0 };
	uint8_t pkg_data_iv[0x10] = { 0 };
	uint8_t pkg_signatures[0x40] = { 0 };
}) PKG_FILE_HEADER;

// Extended PKG header, found in PSV packages
PACK(typedef struct PKG_EXT_HEADER {
	char magic[4] = { 0 };
	uint32_t unknown_01 = 0;
	uint32_t header_size = 0;
	uint32_t data_size = 0;
	uint32_t data_offset = 0;
	uint32_t data_type = 0;
	uint64_t pkg_data_size = 0;

	uint32_t padding_01 = 0;
	uint32_t data_type2 = 0;
	uint32_t unknown_02 = 0;
	uint32_t padding_02 = 0;
	uint64_t padding_03 = 0;
	uint64_t padding_04 = 0;
}) PKG_EXT_HEADER;

typedef struct PKG_METADATA_ENTRY {
	uint32_t type = 0;
	uint32_t size = 0;
} PKG_METADATA_ENTRY;

typedef struct PKG_METADATA {
	uint32_t drm_type = 0;           //Record type 0x1 (for trial-enabled packages, drm is either 0x3 or 0xD)
	uint32_t content_type = 0;       //Record type 0x2
	uint32_t package_flags = 0;      //Record type 0x3
	uint32_t item_table_offset = 0;  //Record type 0xD, offset 0x0
	uint32_t item_table_size = 0;	 //Record type 0xD, offset 0x4
	uint32_t sfo_offset = 0;         //Plaintext SFO copy, record type 0xE, offset 0x0
	uint32_t sfo_size = 0;           //Record type 0xE, offset 0x4
} PKG_METADATA;

typedef enum PKG_TYPE {
	PKG_TYPE_PS3 = 0x1,
	PKG_TYPE_PSV = 0x2
} PKG_TYPE;

typedef enum PKG_METADATA_TYPE {
	PKG_META_DRM_TYPE = 0x1,
	PKG_META_CONTENT_TYPE = 0x2,
	PKG_META_PACKAGE_FLAGS = 0x3,
	PKG_META_PACKAGE_SIZE = 0x4,
	PKG_META_MAKE_PKG_EXE_VERSION = 0x5,
	PKG_META_APP_VERSION = 0x6,
	PKG_META_QA_DIGEST = 0x7,
	PKG_META_REQUIRED_SYS_VERSION = 0x8,
	PKG_META_UNK_9 = 0x9,
	PKG_META_INSTALL_DIRECTORY = 0xA,
	PKG_META_UNK_B = 0xB,
	PKG_META_UNK_C = 0xC,
	PKG_META_FILE_ITEM_INFO = 0xD,
	PKG_META_SFO = 0xE,
	PKG_META_UNK_F = 0xF,
	PKG_META_ENTIRETY_INFO = 0x10,
	PKG_META_PUBLISHINGTOOLS_VERISION = 0x11,
	PKG_META_SELF_INFO = 0x12
} PKG_METADATA_TYPE;

typedef enum PKG_FILE_TYPE {
	PKG_TYPE_FILE = 0x3,
	PKG_TYPE_DIR = 0x4,
	PKG_TYPE_SELF = 0xE,
	PKG_TYPE_PFS_KEYSTONE = 0x10,
	PKG_TYPE_PFS_FILE = 0x11,
	PKG_TYPE_PFS_DIR = 0x12,
	PKG_TYPE_PFS_TEMP_BIN = 0x13,
	PKG_TYPE_PFS_CLEARSIGN = 0x15,
	PKG_TYPE_SCESYS_RIGHT_SUPRX = 0x16,
	PKG_TYPE_SCESYS_CERT_BIN = 0x17,
	PKG_TYPE_SCESYS_DIGS_BIN = 0x18
} PKG_FILE_TYPE;

typedef enum PKG_CONTENT_TYPE {
	PKG_TYPE_UNK_PS3 = 0x1,
	PKG_TYPE_UNK_2 = 0x2,
	PKG_TYPE_UNK_3 = 0x3,
	PKG_TYPE_PS3_GAMEDATA = 0x4,
	PKG_TYPE_PS3_GAMEEXEC = 0x5,
	PKG_TYPE_PSX = 0x6,
	PKG_TYPE_PSP = 0x7,
	PKG_TYPE_UNK_8 = 0x8,
	PKG_TYPE_PS3_THEME = 0x9,
	PKG_TYPE_PS3_WIDGET = 0xA,
	PKG_TYPE_PS3_LICENSE = 0xB,
	PKG_TYPE_PS3_VSH_MODULE = 0xC,
	PKG_TYPE_PS3_PSN_AVATAR = 0xD,
	PKG_TYPE_PSP_GO = 0xE,
	PKG_TYPE_PSP_MINIS = 0xF,
	PKG_TYPE_PSP_NEO_GEO = 0x10,
	PKG_TYPE_PS3_VMC = 0x11,
	PKG_TYPE_PS3_PS2 = 0x12,
	PKG_TYPE_UNK_13 = 0x13,
	PKG_TYPE_PS3_PSP_REMASTER = 0x14,
	PKG_TYPE_VITA_APP = 0x15,
	PKG_TYPE_VITA_DLC = 0x16,
	PKG_TYPE_VITA_LIVEAREA = 0x17,
	PKG_TYPE_PSM = 0x18,
	PKG_TYPE_WEB_TV = 0x19,
	PKG_TYPE_PSM_UNITY = 0x1D,
	PKG_TYPE_VITA_THEME = 0x1F
} PKG_CONTENT_TYPE;

typedef enum PKG_REVISION {
	PKG_REVISION_DEBUG = 0x00,
	PKG_REVISION_FINALIZED = 0x80
} PKG_REVISION;

typedef enum PKG_PACKAGE_FLAGS {
	PKG_FLAG_EBOOT_PBP = 0x2,
	PKG_FLAG_LICENSE_REQUIRED = 0x4,
	PKG_FLAG_MEMORY_CARD_INSTALL = 0x8,
	PKG_FLAG_PATCH_FILE = 0x10
} PKG_PACKAGE_FLAGS;

typedef enum PKG_KEY_ID {
	PKG_KEYID_PS3 = 1,
	PKG_KEYID_VITA = 2,
	PKG_KEYID_VITA_LIVEAREA = 3,
	PKG_KEYID_PSM = 4,
} PKG_KEY_ID;

#endif