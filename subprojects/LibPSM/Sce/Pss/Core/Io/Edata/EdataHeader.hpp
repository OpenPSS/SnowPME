#ifndef LIB_PSS_EDATAHEADER_H
#define LIB_PSS_EDATAHEADER_H 1
#include <iostream>
#include <cstdint>

namespace Sce::Pss::Core::Io::Edata {
	typedef struct _EdataHeader {
		char     Magic[0x4] = { 0 };
		uint32_t Version = 0;
		uint64_t FileSize = 0;
		uint32_t PsseType = 0;
		char     ContentId[0x2C] = { 0 };
		uint8_t  Md5Hash[0x10] = { 0 };
		uint8_t  FileName[0x20] = { 0 };
		uint8_t  FileIv[0x10] = { 0 };
		uint8_t  Unk[0x600] = { 0 };
	} EdataHeader;
}

#endif