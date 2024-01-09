#ifndef LIB_PSS_EDATA_HEADER_H
#define LIB_PSS_EDATA_HEADER_H 1
#include <iostream>

namespace Sce::Pss::Core::Edata {
	typedef struct EdataHeader {
		char     Magic[0x4];
		uint32_t Version;
		uint64_t FileSize;
		uint32_t PsseType;
		char     ContentId[0x2C];
		uint8_t  Md5Hash[0x10];
		uint8_t  FileName[0x20];
		uint8_t  FileIv[0x10];
		uint8_t  Unk[0x600];
	} EdataHeader;
}

#endif