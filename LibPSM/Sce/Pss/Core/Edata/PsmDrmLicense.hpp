#ifndef LIB_PSM_LICENSE_H
#define LIB_PSM_LICENSE_H 1
#include <iostream>

namespace Sce::Pss::Core::Edata {
	typedef struct ScePsmDrmLicense {
		char Magic[0x8];
		uint32_t Unk1;
		uint32_t Unk2;
		uint64_t AccountId;
		uint32_t Unk3;
		uint32_t Unk4;
		uint64_t StartTime;
		uint64_t ExpirationTime;
		uint8_t ActivationChecksum[0x20];
		char ContentId[0x30];
		uint8_t Unk5[0x80];
		uint8_t Unk6[0x20];
		uint8_t Key[0x10];
		uint8_t Signature[0x1D0];
		uint8_t RsaSignature[0x100];
	} ScePsmDrmLicense;
}

#endif