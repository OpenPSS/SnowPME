#ifndef LIB_PSS_PSMDLLS_H
#define LIB_PSS_PSMDLLS_H 1
#include <cstdint>
#include <string>

#define DLL_BUFFER_ALLOC_SIZE (0x300000)

namespace Sce::Pss::Core::Mono::PsmDlls {

	static std::string PsmDllFilenameList[3]{
		"mscorlib.dll",
		"System.dll",
		"Sce.PlayStation.Core.dll"
	};

	enum class PssSystemFileEnum {
		MSCORLIB = 0,
		SYSTEM = 1,
		SCE_PLAYSTATON_CORE = 2,
		NONE = 3,
	};


	inline uint8_t SystemSha1[3][0x14] {
		{ 0x3B, 0x59, 0x22, 0x3E, 0x4E, 0x1E, 0x04, 0xE3, 0xD8, 0x97, 0x95, 0xC0, 0x09, 0x0D, 0x30, 0x3D, 0x5B, 0x95, 0x03, 0x33 }, // From PSM SDK
		{ 0xE2, 0x9F, 0xB4, 0x6A, 0xB7, 0xC2, 0x88, 0x5A, 0xDA, 0x38, 0x11, 0x0E, 0x52, 0x37, 0x5E, 0x53, 0x3D, 0x35, 0x0A, 0x0B }, // From PSVita
		{ 0x5D, 0xF4, 0xB9, 0xC3, 0xC7, 0xC8, 0x3E, 0x12, 0xB5, 0x0A, 0x7F, 0x7A, 0x44, 0xF9, 0xBB, 0x92, 0x94, 0xEA, 0x18, 0xAB }  // From Android
	};

	inline uint8_t MscorlibSha1[3][0x14] {
		 { 0xB9, 0x27, 0x1E, 0x6D, 0xCA, 0x4F, 0xDB, 0x26, 0x37, 0xEF, 0xC5, 0x26, 0x44, 0xBF, 0x0E, 0xD0, 0x4A, 0x61, 0xE5, 0x0E }, // From PSM SDK
		 { 0x87, 0x33, 0x1A, 0x39, 0x38, 0x61, 0xD9, 0x06, 0x2F, 0x39, 0x61, 0xDE, 0x94, 0xFC, 0xBA, 0x1F, 0x0D, 0xBF, 0x80, 0x01 }, // From PSVita
		 { 0xE9, 0x79, 0x92, 0x1A, 0xCF, 0x36, 0x90, 0x2A, 0x1C, 0x45, 0x2E, 0xEC, 0xF4, 0xC0, 0xE1, 0xA6, 0x56, 0xFA, 0x24, 0xB2 }  // From Android
	};

	inline uint8_t ScePlayStationCoreSha1[3][0x14]{
		{ 0x95, 0x6F, 0x06, 0xED, 0x23, 0xE0, 0x74, 0xD3, 0xE4, 0x5F, 0x5A, 0x89, 0xA3, 0x50, 0x75, 0x56, 0x69, 0xBB, 0xBA, 0x92 }, // From PSM SDK
		{ 0x76, 0x97, 0xB3, 0x71, 0xA4, 0x7F, 0x58, 0x65, 0x65, 0xEC, 0x61, 0x3D, 0x04, 0xCF, 0x67, 0xE9, 0x34, 0x8E, 0x28, 0xAD }, // From PSVita
		{ 0x4E, 0x08, 0x40, 0x1E, 0x7C, 0xFE, 0x96, 0x0A, 0x89, 0x28, 0x85, 0x9B, 0x5A, 0xE7, 0x02, 0x71, 0x6E, 0x5C, 0x84, 0xC4 }  // From Android
	};
}

#endif