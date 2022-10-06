#ifndef SNOW_PME_CGX_H
#define SNOW_PME_CGX_H 1
#include <string>

namespace SnowPME::Graphics {
	typedef struct CGXVarientTableEntry {
		uint32_t nullSeperatorListPtr;
		uint32_t varientListPtr;
		uint32_t varientCount;
		char unk0[0x14];
	} CGXVarientTableEntry;

	typedef struct CGXVarient {
		char language[4];
		uint32_t sourcePtr;
		uint32_t sourceSz;
	};

	typedef struct CGXHeader {
		char magic[4];
		char cgxVer[4];
		char glesVer[4];
		uint32_t flags;
		char unk0[8];
		uint32_t varientTablePtr;
		char unk1[0x24];
		char hash[0x10];
	} CGXHeader;
}

#endif